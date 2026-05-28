# M2AP-ogalexan-lvagtben

ShuffleHandler 

Quantitative metric to determining the effectiveness of the randomization algorithms. 

Checking for randomness, 

The five boolean testing functions in order to test randomness are:
- checkNoElementsLost(vector<int>& v, string s); 
- checkAllElementsChangedPosition(vector<int>& v, string s); 
- checkAllElementsHaveDifferentNeighbors(vector<int>& v, string s); 
- hasMadeUpItems(vector<int>& v, string s); 
- checkReversed(vector<int>& v, string s);

checkNoElementsLost check the randomized vectors for missing numbers from 0 to 100 

checkALlElementsChangedPosition checks that each individual number is no longer in the assigned spot of an ordered vector of integers. For each integer that is in their original spot in the ordered vector, a counter is increased. If the randomized vector has more than 20% of the same placements as the ordered vector, the function returns false and is not considered to pass our randomized test. 

checkAllElementsHaveDifferentNeighbors compares the 

hasMadeUpItems tests if the randomized vectors have any integers that are not in the range 0 to 100. 

checkReversed checks that the randomized vector is not in the numerical order from 100 to 0. If the number of integers that line up with the reverse oder of the vector is more than 20% (size of the vector divided by 5), the randmoized vector does not pass the ReverseCheck.


Luke's randomized vector passed ...


Olivia's randomized vector passed ... 

In conclusion, 