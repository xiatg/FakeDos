#ifndef APP_TEXTEDITOR_H
#define APP_TEXTEDITOR_H

#include <string>
#include <vector>
#include <taskManagement.h>

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

    // Hang on editor by store text data in memory and then close the editor
    bool HangOnEditor(int taskid, std::vector <std::string> user_name, std::string username, std::string & jsonmem,
                      PCB_type (&mem)[100],
                      vector<PCB_type> & runningQueue,
                      vector<PCB_type> & blockQueue,
                      vector<PCB_type> & readyQueue);
    
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
void editText(EditorBuffer &editor, vector <string> user_name, string username, string & jsonmem, int taskid,
              PCB_type (&mem)[100],
              vector<PCB_type> & runningQueue,
              vector<PCB_type> & blockQueue,
              vector<PCB_type> & readyQueue);

// Print a command list for editor operations
void editorHelp();

// Initialize editor with data store in memory if it is a wake-up task
void TextEditor(int taskid, bool wakeup, string & jsonmem,
                string username, vector<string> user_name, PCB_type (&mem)[100],
                vector<PCB_type> & runningQueue,
                vector<PCB_type> & blockQueue,
                vector<PCB_type> & readyQueue);

#endif // APP_TEXTEDITOR_H


