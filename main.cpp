#include "text_editor.cpp"
#include <iostream>
#include <limits>

int main() {
    TextEditor editor;
    int choice;
    int line, index, number_of_symbols;
    std::string text_to_append, filename, text_to_find;

    while (true) {
        std::cout << "\nText Editor Menu:\n";
        std::cout << "1. Append Text\n";
        std::cout << "2. Start New Line\n";
        std::cout << "3. Insert Text\n";
        std::cout << "4. Delete Text\n";
        std::cout << "5. Replace Text\n";
        std::cout << "6. Copy Text\n";
        std::cout << "7. Cut Text\n";
        std::cout << "8. Paste Text\n";
        std::cout << "9. Save to File\n";
        std::cout << "10. Load from File\n";
        std::cout << "11. Print Text\n";
        std::cout << "12. Search Text\n";
        std::cout << "13. Undo\n";
        std::cout << "14. Redo\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
            case 1:
                std::cout << "Enter text to append: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, text_to_append);
                editor.append_text(text_to_append);
                break;
            case 2:
                editor.start_new_line();
                break;
            case 3:
                std::cout << "Enter line, index, and text to insert: ";
                std::cin >> line >> index;
                std::cin.ignore();
                std::getline(std::cin, text_to_append);
                editor.insert_text(line, index, text_to_append);
                break;
            case 4:
                std::cout << "Enter line, index, and number of symbols to delete: ";
                std::cin >> line >> index >> number_of_symbols;
                editor.delete_text(line, index, number_of_symbols);
                break;
            case 5:
                std::cout << "Enter line, index, number of symbols to replace, and new text: ";
                std::cin >> line >> index >> number_of_symbols;
                std::cin.ignore();
                std::getline(std::cin, text_to_append);
                editor.replaceText(line, index, number_of_symbols, text_to_append);
                break;
            case 6:
                std::cout << "Enter line, index, and number of symbols to copy: ";
                std::cin >> line >> index >> number_of_symbols;
                editor.copyText(line, index, number_of_symbols);
                break;
            case 7:
                std::cout << "Enter line, index, and number of symbols to cut: ";
                std::cin >> line >> index >> number_of_symbols;
                editor.cutText(line, index, number_of_symbols);
                break;
            case 8:
                std::cout << "Enter line and index to paste: ";
                std::cin >> line >> index;
                editor.paste_text(line, index);
                break;
            case 9:
                std::cout << "Enter filename to save: ";
                std::cin >> filename;
                editor.save_to_file(filename);
                break;
            case 10:
                std::cout << "Enter filename to load: ";
                std::cin >> filename;
                editor.load_from_file(filename);
                break;
            case 11:
                editor.print_text();
                break;
            case 12:
                std::cout << "Enter text to search: ";
                std::cin.ignore();
                std::getline(std::cin, text_to_find);
                editor.search_text(text_to_find);
                break;
            case 13:
                editor.undo();
                break;
            case 14:
                editor.redo();
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}