void jsontrial() {

    Json::Reader reader;
    Json::Value json_object;

    char *buffer;
    buffer = getcwd(NULL, 0);
    string route(buffer);

    cout << route + "\\config_doc.json";

    ifstream fin;
    fin.open(route + "\\config_doc.json");

    string json_document;
    char ch;

    while (fin.get(ch)) {
        json_document += ch;
    }

    cout << json_document;

    reader.parse(json_document, json_object);
    std::cout << json_object["encoding"] << std::endl;
    std::cout << json_object["age"] << std::endl;

//    ofstream fout;
//    fout.open("config_doc.txt");

//    Json::StyledWriter styled_writer;

//    string str = styled_writer.write(root);

//    fout << str;

//    fout.close();

}