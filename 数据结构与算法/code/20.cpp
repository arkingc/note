class Solution {
public:
    bool isNumeric(char* string)
    {
        if(!string)
            return false;
        
        const char *curr = string;
        bool findE = false,findPoint = false;
        int positionOfE;
        while(*curr != '\0'){
            if(*curr == '+' || *curr == '-'){
                if(curr == string || (findE && (curr - string) == (positionOfE + 1) && *(curr + 1) != '\0')){
                    curr++;
                    continue;
                }
                return false;
            }
            else if(*curr == 'E' || *curr == 'e'){
                //只能在中间
                if(!findE && curr != string && *(curr + 1) != '\0'){
                    findE = true;
                    positionOfE = curr - string;
                    curr++;
                    continue;
                }
                return false;
            }
            else if(*curr == '.'){
                if(findE || findPoint)
                    return false;
                findPoint = true;
            }
            else if(*curr < '0' || *curr > '9'){
                return false;
            }
            curr++;
        }
        
        return true;
    }

};