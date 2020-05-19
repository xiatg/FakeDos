#ifndef EDITORBUFFER_H
#define EDITORBUFFER_H
#include <string>

class EditorBuffer {
public:
    // Constructor
    EditorBuffer();
    EditorBuffer(const EditorBuffer &value);

    ~EditorBuffer();

    void moveCursorForward();
    void moveCursorBackward();

    void moveCursorToStart();
    void moveCursorToEnd();

    void insertCharacter(char ch);

    //void insertString(std::string str);

    void deleteCharter();

    void showContents();

    void copyInternalData(const EditorBuffer& value);

    void debug();

private:
    struct Cell{
        char ch;
        Cell *link;
    };
    // Instance variables
    Cell *start;
    Cell *cursor;


};


void editText(EditorBuffer &editor);

void editorHelp();

#endif // EDITORBUFFER_H
