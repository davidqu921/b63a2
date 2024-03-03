/*
 * Our min-heap implementation.
 *
 * Author (starter code): A. Tafliovich.
 */

#include "minheap.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ROOT_INDEX 1
#define NOTHING -1

/*************************************************************************
 ** Suggested helper functions -- to help designing your code
 *************************************************************************/

/* Swaps contents of heap->arr[index1] and heap->arr[index2] if both 'index1'
 * and 'index2' are valid indices for minheap 'heap'. Has no effect
 * otherwise.
 */
void swap(MinHeap* heap, int index1, int index2){
       if (isValidIndex(heap,index1) && isValidIndex(heap,index2)){
              int priorityIndex1 = priorityAt(heap,index1);
              int idIndex1 = idAt(heap,index1);
              int priorityIndex2 = priorityAt(heap,index2);
              int idIndex2 = idAt(heap,index2);

              heap->arr[index1].priority = priorityIndex2;
              heap->arr[index1].id = idIndex2;

              heap->arr[index2].priority = priorityIndex1;
              heap->arr[index2].id = priorityIndex1;

              heap->indexMap[idIndex1] = index2;
              heap->indexMap[idIndex2] = index1;

       }
}

/* Bubbles up the element newly inserted into minheap 'heap' at index
 * 'nodeIndex', if 'nodeIndex' is a valid index for heap. Has no effect
 * otherwise.
 */
void bubbleUp(MinHeap* heap, int nodeIndex){
       if (isValidIndex(heap,nodeIndex)){
              int nodeId = idAt(heap,nodeIndex);    // stay constant
              int nodePriority = priorityAt(heap,nodeIndex); // stay constant

              int parentIndex = parentIdx(heap,nodeIndex); // need to update
              int parentPriority = priorityAt(heap,parentIndex); // need to update

              while(parentIndex != NOTHING && parentPriority > nodePriority){
                     swap(heap,parentIndex,nodeIndex);
                     nodeIndex = indexOf(heap,nodeId);
                     parentIndex =  parentIdx(heap,nodeIndex);
                     parentPriority = priorityAt(heap,parentIndex);
              }

       }
}

/* Bubbles down the element newly inserted into minheap 'heap' at the root,
 * if it exists. Has no effect otherwise.
 */
void bubbleDown(MinHeap* heap){
       int root = ROOT_INDEX;
       if (heap->size > 1){
              int rootId = idAt(heap,root);
              int rootPriority = priorityAt(heap,root);

              int leftIndex = leftIdx(heap,root);

              int rightIndex = rightIdx(heap,root);

              while (leftIndex != NOTHING){
                     int leftId = idAt(heap,leftIndex);
                     int leftPriority = priorityAt(heap,leftIndex);

                     if (rightIndex != NOTHING){
                            int rightId = idAt(heap,rightIndex);
                            int rightPriority = priorityAt(heap,rightIndex);

                            if (rootPriority > leftPriority && leftPriority < rightPriority){
                                   swap(heap,root,leftIndex);
                            }
                            else if(rootPriority > rightPriority && rightPriority < leftPriority){
                                   swap(heap,root,rightIndex);
                            }

                     }

                     else if (rightIndex == NOTHING){
                            if(rootPriority > leftPriority){
                                   swap(heap,root,leftIndex);
                            }
                     }

                      root = indexOf(heap,rootId);
                      int leftIndex = leftIdx(heap,root);

              }
       }
}

/* Returns the index of the left child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such left
 * child.
 */
int leftIdx(MinHeap* heap, int nodeIndex){
       if (nodeIndex*2 <= heap->size){
              return nodeIndex*2;

       }
       else{
              return NOTHING;
       }
}

/* Returns the index of the right child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such right
 * child.
 */
int rightIdx(MinHeap* heap, int nodeIndex){
       if (nodeIndex*2+1 <= heap->size){
              return nodeIndex*2+1;
       }
       else{
              return NOTHING;
       }
}

/* Returns the index of the parent of a node at index 'nodeIndex' in minheap
 * 'heap', if such exists.  Returns NOTHING if there is no such parent.
 */
int parentIdx(MinHeap* heap, int nodeIndex){
       if (nodeIndex = 1 || (heap->size) < 2){
              return NOTHING;
       }
       else{
              return (int)(nodeIndex/2);
       }
}


/* Returns True if 'maybeIdx' is a valid index in minheap 'heap', and 'heap'
 * stores an element at that index. Returns False otherwise.
 */
bool isValidIndex(MinHeap* heap, int maybeIdx){
       if (maybeIdx <= heap->size){
              return true;
       }
       else{
              return false;
       }
}

/* Returns node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
HeapNode nodeAt(MinHeap* heap, int nodeIndex){
       return heap->arr[nodeIndex];
}

/* Returns priority of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
int priorityAt(MinHeap* heap, int nodeIndex){
       return nodeAt(heap,nodeIndex).priority;
}

/* Returns ID of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
int idAt(MinHeap* heap, int nodeIndex){
       return nodeAt(heap,nodeIndex).id;
}

/* Returns index of node with ID 'id' in minheap 'heap'.
 * Precondition: 'id' is a valid ID in 'heap'
 *               'heap' is non-empty
 */
int indexOf(MinHeap* heap, int id){
       for (int index = ROOT_INDEX; index <= heap->size; index++){
              if (idAt(heap,index) == id){
                     return index;
              }
       }
       // return heap->indexMap[id];
}

/*********************************************************************
 * Required functions
 ********************************************************************/
/* Returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode getMin(MinHeap* heap){
       return heap->arr[ROOT_INDEX];
       
       //int size = heap->size;
       //int minPriority = priorityAt(heap,ROOT_INDEX);
       //int minIndex = ROOT_INDEX;
       //for (int i = ROOT_INDEX + 1; i <= size; i++){
       //       if (priorityAt(heap,i) < minPriority){
       //              minPriority = priorityAt(heap,i);
       //              minIndex = i;
       //       }
       //}
       //return nodeAt(heap,minIndex);

}

/* Removes and returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode extractMin(MinHeap* heap){
       HeapNode minNode = getMin(heap);
       int minId = minNode.id;
       int lastNodeId = idAt(heap,heap->size);
       int lastNodePriority = priorityAt(heap,heap->size);

       minNode.id = lastNodeId;
       minNode.priority = lastNodePriority;

       heap->size = heap->size - 1;
       heap->indexMap[minId] = NOTHING;
       heap->indexMap[lastNodeId] = ROOT_INDEX;

       bubbleDown(heap);
       return minNode;

}

/* Inserts a new node with priority 'priority' and ID 'id' into minheap 'heap'.
 * Precondition: 'id' is unique within this minheap
 *               0 <= 'id' < heap->capacity
 *               heap->size < heap->capacity
 */
void insert(MinHeap* heap, int priority, int id){
       int newIndex = heap->size + 1;
       // HeapNode *newNode = malloc(sizeof(HeapNode));
       HeapNode *newNode = &(heap->arr[newIndex]);
       newNode->id = id;
       newNode->priority = priority;
       heap->indexMap[id] = newIndex;
       heap->size = heap->size + 1;
       bubbleUp(heap,newIndex);
}

/* Returns priority of the node with ID 'id' in 'heap'.
 * Precondition: 'id' is a valid node ID in 'heap'.
 */
int getPriority(MinHeap* heap, int id){
       int index = heap->indexMap[id];
       int priority = priorityAt(heap,index);
       return priority;
}

/* Sets priority of node with ID 'id' in minheap 'heap' to 'newPriority', if
 * such a node exists in 'heap' and its priority is larger than
 * 'newPriority', and returns True. Has no effect and returns False, otherwise.
 * Note: this function bubbles up the node until the heap property is restored.
 */
bool decreasePriority(MinHeap* heap, int id, int newPriority){
       if (id >=0 && id < heap->size && heap->indexMap[id] != NOTHING){
              int index = heap->indexMap[id];
              int priority = priorityAt(heap,index);
              if (priority > newPriority){
                     heap->arr[index].priority = newPriority;
                     bubbleUp(heap,index);
                     return true;
              }
              else{
                     return false;
              }
       }
       return false;
}

/* Prints the contents of this heap, including size, capacity, full index
 * map, and, for each non-empty element of the heap array, that node's ID and
 * priority. */
void printHeap(MinHeap* heap){
       int size = heap->size;
       int capacity = heap->capacity;
       int *indexMap = heap->indexMap;
       HeapNode *arr = heap->arr;
       printf("Heap Information\n");
       printf("This heap has a size of %d\n", size);
       printf("The capacity is %d\n", capacity);
       printf("The indexMap: ");
       for (int i=0; i<capacity; i++){ // print full index map including some id is currently not in heap
              printf("%d ", indexMap[i]);
       }
       printf("\n");
       for (int j=1; j<=size; j++){ // print each HeapNode info in arr
              printf("The node on index %d has Priority %d and ID %d\n",j,priorityAt(heap,j),idAt(heap,j));
       }


}

/* Returns a newly created empty minheap with initial capacity 'capacity'.
 * Precondition: capacity >= 0
 */
MinHeap* newHeap(int capacity){
       MinHeap *newHeap = malloc(sizeof(MinHeap));
       newHeap->size = 0;
       newHeap->capacity = capacity;
       int *indexMap = malloc(capacity*sizeof(int));
       for (int i=0; i<capacity; i++){
              indexMap[i] = NOTHING;
       }
       HeapNode *arr = malloc(capacity*sizeof(HeapNode));
       for (int i=0; i<capacity; i++){
              arr[i].id = NOTHING;
              arr[i].priority = NOTHING; 
       }
       return newHeap;
}

/* Frees all memory allocated for minheap 'heap'.
 */
void deleteHeap(MinHeap* heap){
       free(heap->indexMap);
       free(heap->arr);
}
/*********************************************************************
 ** Helper function provided
 *********************************************************************/
void printHeap(MinHeap* heap) {
  printf("MinHeap with size: %d\n\tcapacity: %d\n\n", heap->size,
         heap->capacity);
  printf("index: priority [ID]\t ID: index\n");
  for (int i = 0; i < heap->capacity; i++)
    printf("%d: %d [%d]\t\t%d: %d\n", i, priorityAt(heap, i), idAt(heap, i), i,
           indexOf(heap, i));
  printf("%d: %d [%d]\t\t\n", heap->capacity, priorityAt(heap, heap->capacity),
         idAt(heap, heap->capacity));
  printf("\n\n");
}
