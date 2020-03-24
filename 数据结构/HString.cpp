#include <iostream>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <vector>

class HString {
private:
    char* ch;
    size_t length;

    void copyFromCharArray(const char* chars) {
        if (ch) {
            free(ch);
            ch = nullptr;
        }

        length = std::strlen(chars);

        if (length) {
            ch = (char*)malloc((length + 1) * sizeof(char));

            if (ch == nullptr) {
                throw std::exception("memory ran out");
            }

            std::strcpy(ch, chars);
            ch[length] = 0;
        }
    }

public:
    HString() : ch(nullptr), length(0) {
    }

    HString(const HString& str) : ch(nullptr), length(0) {
        copyFromCharArray(str.ch);
    }

    HString(const char* str) : ch(nullptr), length(0) {
        copyFromCharArray(str);
    }

    HString(HString&& str) : ch(nullptr), length(0) {
        copyFromCharArray(str.ch);
        str.clearString();
    }

    HString& operator =(const char* chars) {
        copyFromCharArray(chars);
        return *this;
    }

    HString& operator =(const HString& s) {
        if (this != &s) {
            copyFromCharArray(s.ch);
        }
        
        return *this;
    }

    HString operator +(const HString& s) const {
        char* temp = (char*)malloc((this->length + s.length) * sizeof(char));
        if (temp == nullptr) {
            throw std::exception("memory ran out");
        }

        std::strcpy(temp, this->ch);
        std::strcat(temp, s.ch);

        return HString{temp};
    }

    inline const char* getCString() const {
        return ch;
    }

    inline size_t getStrLength() { 
        return this->length;
    }

    void clearString() {
        if (ch) { 
            free(ch); ch = nullptr; 
        }

        length = 0;
        return;
    }

    HString getSubString(const size_t& pos, const size_t& len) {
        if (pos > length - 1 || len < 1 || len + pos > length) {
            throw std::exception("index out of range");
        }
        
        char* temp = (char*)malloc(sizeof(char) * (len + 1));
        if (temp == nullptr) {
            throw std::exception("memory ran out");
        }
        std::strncpy(temp, this->ch + pos, len);
        temp[len] = 0;

        return HString{temp};
    }

    int getIndexWithKMP(const HString& T, const size_t& pos) const {
        int i = 0, j = -1;
        int* next = new int[T.length + 1];
        if (next == nullptr) {
            throw std::exception("memory ran out");
        }

        next[0] = -1;

        while (i < T.length) {
            if (j == -1 || T.ch[i] == T.ch[j])
            {
                i++; j++;
                if (T.ch[i] != T.ch[j]) {
                    next[i] = j;
                } 
                else {
                    next[i] = next[j];
                }
            }
            else {
                j = next[j];
            }
        }

        i = pos;
        j = 0;
        while (i < length && j < T.length) {
            if (ch[i] == T.ch[j]) {
                i++; j++;

                if (j == T.length) {
                    break;
                }
            }
            else {
                j = next[j];
            }
        }

        delete[] next;

        return (j >= (int)T.length) ? i - T.length : -1;
    }

    std::vector<size_t> getAllIndex(const HString& T, size_t pos) {
        HString temp(*this);
        std::vector<size_t> index;

        int res;
        while ((res = temp.getIndexWithKMP(T, pos)) != -1) {
            index.push_back(res);
            temp = temp.getSubString(res + 1, temp.length - res - 1);
            pos = 0;
        }

        return index;
    }

    void insertStr(const size_t& pos, const HString& T) {
        if (pos < 1 || pos > length - 1) {
            throw std::exception("index out of range");
        }

        if (T.length) {
            char* chnew = (char*)malloc((this->length + T.length + 1) * sizeof(char));
            if (chnew == nullptr) {
                throw std::exception("memory ran out");
            }

            if (pos != 0) {
                std::strncpy(chnew, this->ch, pos);
            }
            std::strcpy(chnew + pos, T.ch);
            if (pos != this->length) {
                std::strncpy(chnew + pos + T.length, this->ch + pos, this->length - pos);
            }

            chnew[this->length + T.length] = 0;
            this->copyFromCharArray(chnew);
        }
    }

    int compareWith(const HString& T) const noexcept {
        for (int i = 0; i < this->length && i < T.length; i++)
        {
            if (this->ch[i] != T.ch[i])
                return this->ch[i] - T.ch[i];
        }
        return this->length - T.length;
    }
};

int main()
{
    HString T = "AAABAAAAB";
    HString B = "AAAAB";

    std::cout << T.getStrLength() << " ";
    std::cout << B.getStrLength() << " ";

    T = T + B;
    T.insertStr(3, B);
    std::cout << T.getCString() << " " << T.getStrLength() << std::endl;

    T = T.getSubString(0,5) + T.getSubString(6,6);
    std::cout << T.getCString() << " " << T.getStrLength() << std::endl;
    std::cout << T.getIndexWithKMP(B, 0) << " ";

    auto all = T.getAllIndex(B, 0);
    for (const auto& pos : all) {
        std::cout << pos << " ";
    }
    return 0;
}
