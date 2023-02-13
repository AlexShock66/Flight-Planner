//
// Created by Alex Shockley on 9/17/2020.
//

#ifndef INC_20F_AUTO_IDX_SSTRING_H
#define INC_20F_AUTO_IDX_SSTRING_H


class SString {
private:
    char* data;
    int size;
    int maxSize;
public:
    SString();
    SString(char newWord[]);
    ~SString();
    char *getData() const;
    void setString(char *string);
    int getSize() const;
    SString& operator=(const SString &);
    bool contains(char check[]);
    bool contains(char check[],int startPos);
    SString(const SString &copy);
    SString wordAt(int counter);
    int getNumWords();
    bool operator <(const SString &var) const;
    bool operator >(const SString &var) const;
    bool operator ==(const SString& var) const;
    bool operator !=(const SString& var) const;
    void removePunct();
    char& operator[](int index);
    void toUpper();
    void toLower();
    void removeChar(char charToRemove);
    void removeBetween(char startChar, char endChar);
    SString& operator +=(const char* stringToAdd);
    void moveWordBetweenToFront(char firstChar, char secondChar);
    void removeUntil(char stopChar);

};


#endif //INC_20F_AUTO_IDX_SSTRING_H
