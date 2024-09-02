#pragma once
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

constexpr int DOCUMENT = 0;
constexpr int LIST_ITEM = 1;
constexpr int LIST = 2;
constexpr int QUOTE = 3;
constexpr int PARAGRAPH = 10;
constexpr int INDENTED_CODE = 11;
constexpr int FENCED_CODE = 12;

struct Block {
  int block_type = DOCUMENT;
  bool closed = false;
  std::vector<std::shared_ptr<Block>> blocks = {};
  std::vector<std::string> text = {};
};

inline bool is_container(Block &block) {
  if (block.block_type < 10)
    return true;
  else
    return false;
}

inline bool is_block_terminated(Block &block, std::string line) {
  // TODO if CODE:..
  return line.empty(); // not good enough, compare with "whitespaces or empty"
}

inline bool is_block_with_special_termination(Block &block) {
  if (block.block_type == FENCED_CODE)
    return true;
  else
    return false;
}

struct ContinuedBlockResult {
  std::shared_ptr<Block> block_to_insert = {};
  std::shared_ptr<Block> last_block = {};
  std::string line;
};

inline std::shared_ptr<Block> find_last_block(std::shared_ptr<Block> block) {
  if (block->blocks.empty())
    return block;
  else
    return find_last_block(block->blocks.back());
}

inline ContinuedBlockResult
detect_next_block_to_insert(std::shared_ptr<Block> block, std::string line) {
  ContinuedBlockResult result = {};
  if (block->closed)
    return {};
  if (is_container(*block)) {
    if (!block->blocks.empty()) {
      if (block->block_type == DOCUMENT) {
        result = detect_next_block_to_insert(block->blocks.back(), line);
      } else {
        // TODO list, ... etc.
      }
    }
    if (result.block_to_insert == nullptr)
      result = {block, find_last_block(block), line};
  } else { // leaf block
    if (block->block_type == PARAGRAPH) {
      result = {block, find_last_block(block), line};
    } else if (block->block_type == INDENTED_CODE) {
      if (line.starts_with("    ")) {
        result = {block, find_last_block(block), line.substr(4)};
      }
    }
  }
  if (is_block_with_special_termination(*result.last_block)) {
    result.block_to_insert = result.last_block;
  }
  return result;
}

inline void add_next_line(std::shared_ptr<Block> block, std::string line) {
  ContinuedBlockResult c = detect_next_block_to_insert(block, line);
  if (c.block_to_insert == nullptr)
    throw std::runtime_error("unexpected: no place to insert");
  if (is_container(*c.block_to_insert)) {
    // start a new block

    // TODO detect new type of block + create new block (may be called
    // recursively in case of lists...)
    std::shared_ptr<Block> new_block = std::make_shared<Block>();
    new_block->block_type = PARAGRAPH;
    new_block->text.push_back(c.line);
    c.block_to_insert->blocks.push_back(new_block);
  } else {
    // TODO detect if block is "finished"
    if (is_block_terminated(*c.block_to_insert, c.line)) {
      c.block_to_insert->closed = true;
    } else {
      c.block_to_insert->text.push_back(c.line);
    }
  }
}

inline void print(std::ostream &out, std::shared_ptr<Block> block,
                  int indent = 0) {
  out << std::string(indent, ' ') << "BLOCK:" << block->block_type << std::endl;
  for (std::shared_ptr<Block> b : block->blocks) {
    print(out, b, indent + 2);
  }
}
