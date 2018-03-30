class Solution {
public:
    // Parameters:
    //        numbers:     an array of integers
    //        length:      the length of array numbers
    //        duplication: (Output) the duplicated number in the array number
    // Return value:       true if the input is valid, and there are some duplications in the array number
    //                     otherwise false
    bool duplicate(int numbers[], int length, int* duplication) {
        if(length <= 2)
            return false;
        for(int i = 0;i < length;i++){
            while(numbers[i] != i){
                int m = numbers[i];
                if(m < 0 || m >= length)
                    return false;
                if(m == numbers[m]){
                    *duplication = m;
                    return true;
                }
                numbers[i] = numbers[m];
                numbers[m] = m;
            }
        }
        
        return false;
    }
};