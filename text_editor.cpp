class TextEditor{
#include "text_editor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

size_t TextEditor::get_position(int line, int index) const
{
    int current_line = 0;
    int position_in_current_line = 0;
    size_t position_in_text=0;
    if (line < 0 || index < 0) {
        throw std::out_of_range("Line and index should be positive");
    }
    for (position_in_text = 0; position_in_text<text.length(); ++position_in_text) {
        if (current_line == line) {
            if (position_in_current_line == index) {
            return position_in_text;
            }
        position_in_current_line++;
        }
        if (text[position_in_text] == '\n') {
            current_line++;
            position_in_current_line = 0;
        }
    }
}
//void TextEditor::save_state(int line, int index)


void TextEditor::append_text(const std::string& text_to_append) {
    save_State();
    text+=text_to_append;
}

void TextEditor::start_new_line() {
    save_State();
    text+='\n';
}

void TextEditor::save_to_file(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << text;
        file.close();
        std::cout <<"Text saved to" << filename << std::endl;
    }
    else {
        std::cerr <<"Error opening file" << std::endl;
    }
}

void TextEditor::load_from_file(const std::string& filename) {
    std::ifstream finle(filename);
    if (file.is_open()) {
        std::string loaded_text((std::istreambuf_iterator<char>(file)),
                                 std::istreambuf_iterator<char>());
        file.close();
        save_State();
        text = loaded_text;
    }
    else {
        std::cerr <<"Error opening file" << std::endl;
    }
}

void TextEditor::print_text() {
    if (text.empty()) {
        std::cout <<"Line is empty\n";
    }
    else {
    std::cout << text << "\n";
    }
}
void TextEditor::insert_text(int line, int index, const std::string& text_to_insert) {
    size_t position = get_position(line, index);
    save_State();
    text.insert(position, text_to_insert);
}
void TextEditor::searchText(const std::string& text_to_find) const {
    if (text_to_find.empty()) {
        std::cout <<"Line to search is empty\n";
        return;
    }
    int line = 1;
    int col = 0;
    bool found = false;
    size_t position = 0;
    while((position = text.find(text_to_find, position)) != std::string::npos) {
        int line_for_user=1;
        int col_for_user=0;
        for (size_t i=0; i<position; ++i) {
            if (text[i] == '\n') {
                line_for_user++;
                col_for_user = 0;
            }
            else {
            col_for_user++;
            }
        }
        std::cout << "Found \"" << text_to_find << "\" at line " << line_for_user
                 << ", column " << col_for_user << std::endl;
        bool found = true;
        position = position - text_to_find.length() + 1;
    }
        if (!found) {
        std::cout << "Text \"" << text_to_find << "\" not found\n";
        }
}
void TextEditor:: delete_text(int line, int index, int number_of_symbols) {
    save_State();
    if (number_of_symbols<0) {
        throw std::invalid_argument("You can not delete negative number of symbols\n");
    }
    if (number_of_symbols == 0) {
        return;
    }
    save_State();
    size_t position = get_position(line, index);
    size_t real_symbols_to_delete = std::min((size_t)number_of_symbols, text.length() - position);
    text.erase(pos, actual_symbols_to_delete);
}
void TextEditor::cut_text(int line, int index, int number_of_symbols) {
    save_State();
    if (number_of_symbols < 0) {
        throw std::invalid_argument("You can not cut negative number of symbols\n");
    }
    if (number_of_symbols > 0) {
        clipboard.clear();
        return;
    }
}
//void TextEditor:: copyText(int line, int index, const std::string& text_to_copy) {
    if (number_of_symbols < 0) {
        throw std::invalid_argument("You can not copy negative number of symbols\n");
    }
    else if (number_of_symbols > 0) {

        return;
    }

void TextEditor::paste_text(int line, int index)
{
    save_State();
    size_t position = get_position(line, index);
    if (clipboard.empty()) {
        return;
    }
    text.insert(position, clipboard);
}
void undo();
void redo();
// void insertReplacementText(int line, int index, const std::string& textToInsert);

// }

