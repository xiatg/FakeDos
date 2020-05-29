#ifndef APP_TEXTEDITOR_H
#define APP_TEXTEDITOR_H

#include <string>

/* Editor Buffer: implements a simple text editor.
 * The underlying data structure is a linked list.
 * The codes are referred to the text book. */

class EditorBuffer {
public:
    // Constructor
    EditorBuffer();

    // Destructor
    ~EditorBuffer();

    // Moving cursors
    void moveCursorForward();
    void moveCursorBackward();

    void moveCursorToStart();
    void moveCursorToEnd();

    // Insert a character after cursor
    void insertCharacter(char ch);

    // Delete a charcter after cursor
    void deleteCharter();

    // Show the contents of the editor, as well as the location of cursor
    void showContents();

private:
    /* Cell: the basic unit of linked-list-type editor buffer.
     * Each cell contains a character and a pointer to the next cell.
     */
    struct Cell{
        char ch;
        Cell *link;
    };

    // Instance variables
    Cell *start;
    Cell *cursor;


};

// Open a editor and edit its text
void editText(EditorBuffer &editor);

// Print a command list for editor operations
void editorHelp();


#endif // APP_TEXTEDITOR_H


