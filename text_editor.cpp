#include "text_editor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iterator>

TextEditor::TextEditor() : changes_index(0), text(""), clipboard("") {
    changes.push_back(text);
}

void TextEditor::save_State() {
    if (changes_index < changes.size() - 1) {
        changes.erase(changes.begin() + changes_index + 1, changes.end());
    }
    changes.push_back(text);
    changes_index = changes.size() - 1;
    while (changes.size() > MAX_changes) {
        changes.erase(changes.begin());
    }
}

size_t TextEditor::get_position(int line, int index) const {
    if (line < 0 || index < 0) {
        throw std::out_of_range("Line and index must be non-negative.");
    }
    size_t current_pos = 0;
    int current_line = 0;
    int position_in_current_line = 0;
    while (current_pos < text.length()) {
        if (current_line == line) {
            if (position_in_current_line == index) {
                return current_pos;
            }
            position_in_current_line++;
        }
        if (text[current_pos] == '\n') {
            if (current_line == line && position_in_current_line > index) {
                throw std::out_of_range("Index exceeds line length.");
            }
            current_line++;
            position_in_current_line = 0;
        }
        current_pos++;
    }
    if (current_line < line || (current_line == line && position_in_current_line < index)) {
        throw std::out_of_range("Specified line or index is out of bounds.");
    }
    return text.length();
}

void TextEditor::append_text(const std::string& text_to_append) {
    save_State();
    text += text_to_append;
}

void TextEditor::start_new_line() {
    save_State();
    text += '\n';
}

void TextEditor::insert_text(int line, int index, const std::string& text_to_insert) {
    size_t position = get_position(line, index);
    save_State();
    text.insert(position, text_to_insert);
}

void TextEditor::delete_text(int line, int index, int number_of_symbols) {
    if (number_of_symbols < 0) {
        throw std::invalid_argument("Number of symbols to delete cannot be negative.");
    }
    if (number_of_symbols == 0) {
        return;
    }
    size_t position = get_position(line, index);
    save_State();
    size_t real_symbols_to_delete = std::min((size_t)number_of_symbols, text.length() - position);
    text.erase(position, real_symbols_to_delete);
}

void TextEditor::replaceText(int line, int index, int number_of_symbols_to_replace, const std::string& text_to_insert) {
    if (number_of_symbols_to_replace < 0) {
        throw std::invalid_argument("Number of symbols to replace cannot be negative.");
    }
    size_t pos = get_position(line, index);
    save_State();
    size_t actual_symbols_to_delete = std::min((size_t)number_of_symbols_to_replace, text.length() - pos);
    text.erase(pos, actual_symbols_to_delete);
    text.insert(pos, text_to_insert);
}

void TextEditor::save_to_file(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
        std::cout << "Text saved to " << filename << std::endl;
    } else {
        std::cerr << "Error: Could not open file for saving: " << filename << std::endl;
    }
}

void TextEditor::load_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string loaded_text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        save_State();
        text = loaded_text;
        std::cout << "Text loaded from " << filename << std::endl;
    } else {
        std::cerr << "Error: Could not open file for loading: " << filename << std::endl;
    }
}

void TextEditor::copyText(int line, int index, int number_of_symbols) {
    if (number_of_symbols < 0) {
        throw std::invalid_argument("Number of symbols to copy cannot be negative.");
    }
    if (number_of_symbols == 0) {
        clipboard.clear();
        return;
    }
    size_t position = get_position(line, index);
    size_t real_symbols_to_copy = std::min((size_t)number_of_symbols, text.length() - position);
    clipboard = text.substr(position, real_symbols_to_copy);
}

void TextEditor::cutText(int line, int index, int number_of_symbols) {
    if (number_of_symbols < 0) {
        throw std::invalid_argument("Number of symbols to cut cannot be negative.");
    }
    if (number_of_symbols == 0) {
        clipboard.clear();
        return;
    }
    size_t position = get_position(line, index);
    save_State();
    size_t real_symbols_to_cut = std::min((size_t)number_of_symbols, text.length() - position);
    clipboard = text.substr(position, real_symbols_to_cut);
    text.erase(position, real_symbols_to_cut);
}

void TextEditor::paste_text(int line, int index) {
    if (clipboard.empty()) {
        std::cout << "Clipboard is empty, nothing to paste.\n";
        return;
    }
    size_t position = get_position(line, index);
    save_State();
    text.insert(position, clipboard);
}

void TextEditor::undo() {
    if (changes.empty()) {
        std::cout << "Cannot undo: History is empty.\n";
        return;
    }
    if (changes_index > 0) {
        changes_index--;
        text = changes[changes_index];
        std::cout << "Undo successful.\n";
    } else {
        std::cout << "Cannot undo: Already at the oldest state.\n";
    }
}

void TextEditor::redo() {
    if (changes.empty()) {
        std::cout << "Cannot redo: History is empty.\n";
        return;
    }
    if (changes_index < changes.size() - 1) {
        changes_index++;
        text = changes[changes_index];
        std::cout << "Redo successful.\n";
    } else {
        std::cout << "Cannot redo: Already at the latest state.\n";
    }
}

void TextEditor::print_text() const {
    if (text.empty()) {
        std::cout << "Text is empty.\n";
    } else {
        std::cout << text;
    }
}

void TextEditor::search_text(const std::string& text_to_find) const {
    if (text_to_find.empty()) {
        std::cout << "Search string is empty.\n";
        return;
    }
    size_t position = text.find(text_to_find, 0);
    bool found_any = false;
    while (position != std::string::npos) {
        found_any = true;
        int line_for_user = 1;
        int col_for_user = 1;
        for (size_t i = 0; i < position; ++i) {
            if (text[i] == '\n') {
                line_for_user++;
                col_for_user = 1;
            } else {
                col_for_user++;
            }
        }
        std::cout << "Found \"" << text_to_find << "\" at line " << line_for_user
                  << ", column " << col_for_user << std::endl;
        position = text.find(text_to_find, position + text_to_find.length());
    }
    if (!found_any) {
        std::cout << "Text \"" << text_to_find << "\" not found.\n";
    }
}