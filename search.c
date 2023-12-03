#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ARRAY_SIZE 1048575 // Size of the array

// Comparison function for qsort
int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int binary_search(int *array, int key, int lo, int hi) {
	printf("lo: %d hi:%d\n", lo, hi);
	if (hi == lo + 1) {
		if (array[lo] == key) return lo;
		else return -1;
	}
	int mid = (hi-lo)/2 + lo;
	if (key < array[mid])
		return binary_search(array, key, lo, mid);
	else if (key > array[mid])
		return binary_search(array, key, mid, hi);
	else
		return mid;
}

// Function to find the upper square root of a number
int upper_sqrt(int n) {
    return (int)ceil(sqrt(n));
}

// Function to find the lower square root of a number
int lower_sqrt(int n) {
    return (int)floor(sqrt(n));
}

// A basic structure for tree nodes
typedef struct TreeNode {
    int value;
    struct TreeNode *left, *right;
} TreeNode;

// Function to create a new tree node
TreeNode* newTreeNode(int value) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->value = value;
    node->left = node->right = NULL;
    return node;
}

// Function to build a balanced BST from a sorted array
TreeNode* sortedArrayToBST(int arr[], int start, int end) {
    if (start > end) return NULL;

    // Middle element to make it balanced
    int mid = (start + end) / 2;
    TreeNode *root = newTreeNode(arr[mid]);

    // Recursively build left and right subtrees
    root->left = sortedArrayToBST(arr, start, mid - 1);
    root->right = sortedArrayToBST(arr, mid + 1, end);

    return root;
}

// Function to count the nodes in the BST
int countNodes(TreeNode *root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to perform BFS traversal and map the nodes to an array
void BFS(TreeNode *root, int *bfsArray) {
    if (root == NULL) return;

    int count = countNodes(root);
    int front = 0, rear = 0;
    TreeNode **queue = (TreeNode **)malloc(count * sizeof(TreeNode *));

    // Start with the root
    queue[rear++] = root;

    while (front < rear) {
        TreeNode *current = queue[front++];

        // Add the value of the current node to the array
        *bfsArray++ = current->value;

        // Enqueue left child
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }

        // Enqueue right child
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }

    free(queue);
}


// Utility function to print an array
void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int *array = (int *) malloc(ARRAY_SIZE * sizeof(int));
    int i;

    // Seed the random number generator
    srand(time(NULL));

    // Fill the array with random integers
    for (i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand();
    }
	array[0] = 1000000000;

    // Sort the array
    qsort(array, ARRAY_SIZE, sizeof(int), compare_ints);
	int index = binary_search(array, 1000000000, 0, ARRAY_SIZE);
	printf("index: %d\n", index);

	free(array);

	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original Array: ");
    print_array(arr, n);

	TreeNode *root = sortedArrayToBST(arr, 0, n - 1);

    int *bfsArray = (int *)malloc(n * sizeof(int));
    BFS(root, bfsArray);

    printf("BFS Traversal Order: ");
    print_array(bfsArray, n);

    free(bfsArray);

    return 0;
}

