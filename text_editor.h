#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>

class TextEditor {
private:
    std::string text;
    std::vector<std::string> changes;
    std::string clipboard;
    size_t changes_index;
    static const size_t MAX_changes = 5;

    size_t get_position(int line, int index) const;
    void save_State();

public:
    TextEditor();

    void append_text(const std::string& text_to_append);
    void start_new_line();
    void save_to_file(const std::string& filename);
    void load_from_file(const std::string& filename);
    void print_text() const;
    void insert_text(int line, int index, const std::string& text_to_insert);
    void search_text(const std::string& text_to_find) const;

    void delete_text(int line, int index, int number_of_symbols);
    void cutText(int line, int index, int number_of_symbols);
    void copyText(int line, int index, int number_of_symbols);
    void paste_text(int line, int index);

    void undo();
    void redo();

    void replaceText(int line, int index, int number_of_symbols_to_replace, const std::string& text_to_insert);
};

#endif // TEXTEDITOR_H