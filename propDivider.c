#include <stdio.h>
#include<limits.h>
#include<stdlib.h>

// Global variable for child and property
int arr1[1000], arr2[1000], arr5[1000], propertyCopy[1000], assignedIndexes[1000], len, lenCopy, flag = 0, childCount = 1, propertyCount = 0;

//Fetches property numer when its value is provided
int propertyNumber(int value){
	int i, j, isAssigned;
	for(i = 0; i < lenCopy; i++){
		isAssigned = 0;
		if(propertyCopy[i] == value){  //if value matches
			for(j = 0; j < propertyCount; j++){
				if(assignedIndexes[j] == i)  //check if it is already assigned(for >1 properties of same value)
					isAssigned = 1;
			}
			if(isAssigned == 0){  //if it is not assigned, add to assigned array
				assignedIndexes[propertyCount++] = i;
				return i + 1;
			}
		}
	}
	return 0;  //safety net
}

void print(int arr4[], int pos){
    int start = 0, i, ta = arr4[pos-1], m = 0, z = pos,sum1=0;
	if(flag == 0){
        // By this the user get intimated about the child holding
        printf("\nProperties given to child %d:", childCount++);
        for(i = 0; i < pos; i++){
            printf("\nProperty: %d, Value: %d", propertyNumber(arr1[arr4[i]]), arr1[arr4[i]]);
            sum1+=arr1[arr4[i]];
        }
        // pos variable keep track of no of properties child have
        pos--;
        printf("\nTotal Value = %d\n",sum1);
        // then we update property array with the left out properties
        for(i = 0; i < len; i++){
            if(ta == i && pos >= 0){
                ta = arr4[pos-1];
                pos--;
            }
			else
                arr5[m++] = arr1[i];
        }
        // Also we update the left out length of property array
        len = len - z;
        for(i = 0; i < len; i++)
            arr1[i] = arr5[i];
        // flag is updated to 1 so that no child get properties two times
        flag = 1;
    }
}

// This function will decide if we can give the required sum exactly from the array
int isSubsetSum(int set[], int n, int sum, int arr4[],int pos){
    int a, b;
 
	// Base Cases
    if(sum == 0){
        print(arr4, pos);
        return 1;
    }
    // return 0 if all array is traversed
    if(n == 0)
        return 0;
    // if current value is greater than sum then we leave that and process fro next element
    if(set[n - 1] > sum)
        return isSubsetSum(set, n - 1, sum, arr4, pos);
    a = isSubsetSum(set, n - 1, sum,arr4,pos);
    // If not
    // We add to the property array of child
    arr4[pos] = n - 1;
    b = isSubsetSum(set, n - 1, sum - set[n - 1], arr4, pos + 1);
    // return the true if required sum can be achieved
    return a || b;
}


int main(){
	int i, l, property = 0, child, pr, nt, m, k;
	printf("Fair Property Divider");
	printf("\n\nEnter the number of people: ");
	scanf("%d", &k);
	printf("\nEnter the number of properties: ");
	scanf("%d", &len);
	lenCopy = len;
	for(i = 0; i < len; i++){
		printf("Enter value of property %d: ", i + 1);
		scanf("%d", &arr1[i]);
		propertyCopy[i] = arr1[i];
	}
    // no of child > length of array
    // then give each value to different child
    if(k>=len){
		for(i = 0; i < len; i++){
            printf("\nProperty given to person %d:\nProperty: %d, Value: %d\n", i + 1, propertyNumber(arr1[i]), arr1[i]);
            printf("Total Value = %d\n",arr1[l]);
        }
        for(i = len; i < k; i++){
            printf("\nNo property given to person %d:\nValue: 0\n", i + 1);
            printf("Total Value = 0\n");
        }
	}
	else{
	    child = k;
	    // get the sum of property array
	    for(i = 0; i < len; i++)
            property += arr1[i];
	    for(i = 0; i < k; i++){
            // get the average of property
            pr = property/child;
            nt = 0;
            for(l = 0; l < len; l++){
                // first process if any of property value is greater than average
                // if that's the case give to current child
                if(nt == 1)
                    arr1[l-1]=arr1[l];
                else if(pr <= arr1[l]){
                    printf("\nProperty given to person %d:\nProperty: %d, Value: %d\n", i + 1, propertyNumber(arr1[l]), arr1[l]);
                    printf("Total Value = %d\n",arr1[l]);
                    childCount++;
                    property = property - arr1[l];
                    nt = 1;
                }
            }
            if(nt == 1){
                len--;
                child--;
                continue;
            }
            // If that's not the case then process for suitable value which can be given to child
            while(1){
                int m = isSubsetSum(arr1, len, pr,arr2,0);
                if(m == 1){

                    child--;
                    property = property-pr;
                    break;
                }
                pr++;
            }
            flag = 0;
	    }
	}
	return 0;
}
