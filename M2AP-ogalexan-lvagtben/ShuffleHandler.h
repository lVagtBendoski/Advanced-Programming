//
// Created by bobjo on 10/3/2024.
//

#ifndef SHUFFLEHANDLER_H
#define SHUFFLEHANDLER_H
#include <algorithm>
#include <vector>
#include <iostream>


//#include <bits/stdc++.h>

template<typename shuffleable>

class ShuffleHandler {
private:
    std::vector<shuffleable> vec;

public:
    ShuffleHandler();
    ShuffleHandler(const std::vector<shuffleable>& v) {
        for(int i = 0; i < v.size(); i++) {
            vec.push_back(v[i]);
        }
    }
    std::vector<shuffleable>& getVector() {
        return vec;
    }
    std::vector<shuffleable> shuffleOGALEXAN() {
        std::vector<int> randomNums;
        std::vector<int> listNums;
        std::vector<shuffleable> shuffledNums;

        for (int y = 0; y < vec.size(); ++y) {
            listNums.push_back(y);
        }
        //seeding the 'randomness'
        std::srand(time(0));

        //while listNums is not empty
        while (!listNums.empty()) {
            //random integer
            int j = std::rand() % 101;
            //random number is in listNums
            while (std::find(listNums.begin(), listNums.end(), j) != listNums.end()) {
                //insert into randomNums
                randomNums.push_back(j);

                //https://www.geeksforgeeks.org/how-to-remove-an-element-from-vector-in-cpp/
                //remove from listNums
                auto num = std::find(listNums.begin(), listNums.end(), j);
                if (num != listNums.end()) {
                    listNums.erase(num);
                }
                //new random number
                j = std::rand() % 101;
            }
        }

        for(int i = 0; i < randomNums.size(); i++) {
            shuffledNums.push_back(vec[randomNums[i]]);
        }
        return shuffledNums;

    }

    std::vector<shuffleable> shuffleLVAGTBEN() {
        //https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/#
        srand(time(0));
        std::vector<int> randomIndices;
        std::vector<shuffleable> result;
        std::vector<int>::iterator it;
        int nextIndex;
        int i;
        for(i = 0; i < vec.size(); i++) {
            nextIndex = rand() % (vec.size()-1);
            //make sure that index isn't already used
            if(count(randomIndices.begin(), randomIndices.end(), nextIndex) == 0) {
                //put it in the vector so we can loop through the list of randomly assigned indices later
                randomIndices.push_back(nextIndex);
            }else {
                //try another random number, so it can be more random.
                nextIndex = rand() % (vec.size()-1);
                if(count(randomIndices.begin(), randomIndices.end(), nextIndex) == 0) {
                    randomIndices.push_back(nextIndex);
                }else {
                    // here the vector is probably getting full, or we are unlucky so we will just find an unused index
                    while(count(randomIndices.begin(), randomIndices.end(), nextIndex) != 0) {
                        if(nextIndex < vec.size()-1) {
                            nextIndex++;
                        }else {
                            nextIndex = 0;
                        }
                    }
                    randomIndices.push_back(nextIndex);
                }
            }
        }
        for(i = 0; i < randomIndices.size(); i++) {
            result.push_back(vec[randomIndices[i]]);
        }
        return result;
    }

    std::vector<shuffleable> sort(std::vector<shuffleable> vec) {
        int unsortedStartIndex, insertIndex;
        shuffleable toBeInserted;
        for (unsortedStartIndex = 1; unsortedStartIndex < vec.size(); ++unsortedStartIndex) {
            toBeInserted = vec[unsortedStartIndex];
            // Loop to shift over the larger elements
            insertIndex = unsortedStartIndex - 1;
            while (insertIndex >= 0 && vec[insertIndex] > toBeInserted) {
                vec[insertIndex + 1] = vec[insertIndex];
                --insertIndex;
            }
            //This if statement will catch the two reads that occur if the first half of the conditional
            //is true and the second half is false
            // Put toBeInserted back into vec
            vec[insertIndex + 1] = toBeInserted;

            // Uncomment this line if you want to see each iteration
            //printVec(vec);
        }
        return vec;
    }


    int findIndex(shuffleable item) {
        for(int i = 0; i < vec.size(); i++) {
            if(item == vec[i]) {
                return i;
            }
        }
        std::cout << "item not found" << std::endl;
        return -1;
    }
    //this should work, but I can't figure out how to call it without getting a compiler error
    //that says this function is not defined. probably a problem with how it's called.
    friend std::ostream& operator << (std::ostream& outs, const std::vector<shuffleable>& subject) {
        outs <<'[';
        for(int i = 0; i < subject.size(); i++) {
            outs << " " << subject[i] << " ";
        }
        outs <<']';
        return outs;
    }

};

#endif //SHUFFLEHANDLER_H
