#include "library.h"
#include <iostream>
#include <cstring>
#include <fstream>


using namespace std;

// // Document class
/* setters and getters */
void Document::updateTitle(const char *newTitle){
    _title = new char[strlen(newTitle)+1];
    strcpy(_title, newTitle);
}
void Document::updateYear(int newYear){
    _year = newYear;
}
void Document::updateQuantity(int newQuantity){
    _quantity = newQuantity;
}
char *Document::getTitle(){
    return _title;
}
int Document::getYear(){
    return _year;
}
int Document::getQuantity(){
    return _quantity;
}

/* Used when someone tries to borrow a document, should return 0 on success
* and something else on failure */
int Document::borrowDoc(){
    if (_quantity > 0){
        updateQuantity(_quantity - 1);
        return 0;
    }
    return 1;
}

/* Used when someone returns a document */
void Document::returnDoc(){
    updateQuantity(_quantity + 1);
}


// Novel class
Novel::Novel(const char *title, const char *author, int year, int quantity):Document(){
    _title = new char[strlen(title)+1];
    strcpy(_title, title);
    _author = new char[strlen(author)+1];
    strcpy(_author, author);
    _year = year;
    _quantity = quantity;
}
Novel::~Novel(){
    delete[] _title;
    delete[] _author;
}

document_type Novel::getDocType(){
    return document_type::DOC_NOVEL;
}

void Novel::print(){
    // Novel, title: <title>, author: <author>, year: <year>, quantity: <quantity>
    // printf("Novel, title: %c, author: %c, year: %d, quantity: %d" , getTitle(), getAuthor(), getYear(), getQuantity());
    cout << "Novel, title: " << getTitle() << ", author: " << getAuthor() << ", year: " << getYear() << ", quantity: " << getQuantity()<< endl;
}

void Novel::updateAuthor(const char *newAuthor){
    // *_author = *newAuthor;
    _author = new char[strlen(newAuthor)+1];
    strcpy(_author, newAuthor);
}
char *Novel::getAuthor(){
    return _author;
}


// Comic class
Comic::Comic(const char *title, const char *author, int issue, int year, int quantity):Document(){
    // 
    _title = new char[strlen(title)+1];
    strcpy(_title, title);
    _author = new char[strlen(author)+1];
    strcpy(_author, author);
    _issue = issue;
    _year = year;
    _quantity = quantity;
}

Comic::~Comic(){
    delete [] _title;
    delete [] _author;
}

document_type Comic::getDocType(){
    return document_type::DOC_COMIC;
}

void Comic::print(){
    cout << "Comic, title: " << getTitle() << ", author: " << getAuthor() << ", issue: " << getIssue() << ", year: " << getYear() << ", quantity: " << getQuantity()<< endl;
}

void Comic::updateAuthor(const char *newAuthor){
    // *_author = *newAuthor;
    _author = new char[strlen(newAuthor)+1];
    strcpy(_author, newAuthor);
}
void Comic::updateIssue(int newIssue){
    _issue = newIssue;
}
char *Comic::getAuthor(){
    return _author;
}
int Comic::getIssue(){
    return _issue;
}


// Magazine class
Magazine::Magazine(const char *title, int issue, int year, int quantity): Document(){
    _title = new char[strlen(title)+1];
    strcpy(_title, title);
    _issue = issue;
    _year = year;
    _quantity = quantity;
}
Magazine::~Magazine(){
    delete [] _title;
}

document_type Magazine::getDocType(){
    return document_type::DOC_MAGAZINE;
}

void Magazine::print(){
    cout << "Magazine, title: " << getTitle() << ", issue: " << getIssue() << ", year: " << getYear() << ", quantity: " << getQuantity()<< endl;
}

void Magazine::updateIssue(int newIssue){
    _issue = newIssue;
}
int Magazine::getIssue(){
    return _issue;
}


Library::Library(){};

void Library::print(){
    for (Document * i : _docs){
        i->print();
    }
}

int Library::dumpCSV(const char *filename){

    string input=filename;
	std::ofstream file;
	file.open (input);

    for (Document * i : _docs){
        Novel* NovelPtr = static_cast<Novel*>(i);
        Comic* ComicPtr = static_cast<Comic*>(i);
        Magazine* MagazinePtr = static_cast<Magazine*>(i);

        if (i->getDocType() == 0){
            file << "novel,";
        }
        else if (i->getDocType() == 1){
            file << "comic,";
        }
        else if (i->getDocType() == 2){
            file << "magazine,";
        }

        file << i->getTitle() << ",";

        if (i->getDocType() == 0){
            file << NovelPtr->getAuthor() << ",";
        }
        else if (i->getDocType() == 1){
            file << ComicPtr->getAuthor() << ",";
        }
        else {
            file <<""<< ",";
        }

        if (i->getDocType() == 1){
            file << ComicPtr->getIssue() << ",";
        }
        else if (i->getDocType() == 2){
            file << MagazinePtr->getIssue() << ",";
        }
        else {
            file <<""<< ",";
        }

        file << i->getYear() << ",";
        file << i->getQuantity() << "\n";

    }
    file.close();

    if (file.good()){
        return 0;
    }
    return 1;

}

Document *Library::searchDocument(const char *title){

    for (Document * i: _docs){
        if (strcmp(title, i->getTitle())==0){
            return i;
        }
    }
    return NULL;
}


/* Add/delete a document to/from the library, return 0 on success and
    * something else on failure.  */
int Library::addDocument(Document *d){

    for (Document * i : _docs){
        if (strcmp(i->getTitle(), d->getTitle())==0){
            return 1;
        }
    }
    _docs.push_back(d);

    return 0;

}

int Library::delDocument(const char *title){

    for (int i = 0; i < _docs.size(); i++){
        if (strcmp(_docs[i]->getTitle(), title)==0){
            _docs.erase(_docs.begin() + i);
            return 0;
        }
    }
    return 1;
}

/* Count the number of document of a given type present in the library */
int Library::countDocumentOfType(document_type t){

    int count = 0;
    for (Document * i : _docs){
        if (i->getDocType() == t){
            count += 1;
        }
    }
    return count;
}


int Library::borrowDoc(const char *title){

    for (Document * i : _docs){
        if (strcmp(i->getTitle(), title)==0){
            return (i->borrowDoc());
        }
    }
    return 1;

}

/* Used when someone returns a Library */
int Library::returnDoc(const char *title){

    for (Document * i : _docs){
        if (strcmp(i->getTitle(), title) == 0){
            i->returnDoc();
            return 0;
        }
    }
    return 1;

}
