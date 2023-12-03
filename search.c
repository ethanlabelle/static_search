#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 32767 // Size of the array

// Utility function to print an array
void print_array(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

// Comparison function for qsort
int compare_ints(const void *a, const void *b) {
  int arg1 = *(const int *)a;
  int arg2 = *(const int *)b;

  if (arg1 < arg2)
    return -1;
  if (arg1 > arg2)
    return 1;
  return 0;
}

int binary_search(int *array, int key, int lo, int hi) {
  printf("lo: %d hi:%d\n", lo, hi);
  if (hi == lo + 1) {
    if (array[lo] == key)
      return lo;
    else
      return -1;
  }
  int mid = (hi - lo) / 2 + lo;
  if (key < array[mid])
    return binary_search(array, key, lo, mid);
  else if (key > array[mid])
    return binary_search(array, key, mid, hi);
  else
    return mid;
}

// Function to find the upper square root of a number
int upper_sqrt(int n) { return (int)ceil(sqrt(n)); }

// Function to find the lower square root of a number
int lower_sqrt(int n) { return (int)floor(sqrt(n)); }

// A basic structure for tree nodes
typedef struct TreeNode {
  int value;
  struct TreeNode *left, *right;
} TreeNode;

// Function to create a new tree node
TreeNode *newTreeNode(int value) {
  TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
  node->value = value;
  node->left = node->right = NULL;
  return node;
}

// Helper function to print spaces
void printSpaces(int count) {
  for (int i = 0; i < count; i++) {
    printf(" ");
  }
}

// Recursive function to pretty-print the tree
void printTree(TreeNode *root, int space, int indent) {
  // Base case
  if (root == NULL) {
    return;
  }

  // Increase distance between levels
  space += indent;

  // Process right child first
  printTree(root->right, space, indent);

  // Print current node after space
  // count
  printf("\n");
  printSpaces(space);
  printf("%d\n", root->value);

  // Process left child
  printTree(root->left, space, indent);
}

void freeTree(TreeNode *root) {
  if (!root->left && !root->right) {
    free(root);
    return;
  }
  if (root->left)
    freeTree(root->left);
  if (root->right)
    freeTree(root->right);
  free(root);
}

// Function to calculate the height of the tree
int treeHeight(TreeNode *root) {
  if (root == NULL) {
    // If the node is null, return height as 0
    return 0;
  } else {
    // Calculate the height of left and right subtrees
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    // Return the larger of the two heights plus 1 for the current node
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
  }
}

// Function to build a balanced BST from a sorted array
TreeNode *sortedArrayToBST(int arr[], int start, int end) {
  if (start > end)
    return NULL;

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
  if (root == NULL)
    return 0;
  return 1 + countNodes(root->left) + countNodes(root->right);
}

// Function to perform BFS traversal and map the nodes to an array
void BFS(TreeNode *root, int *bfsArray) {
  if (root == NULL)
    return;

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

int BST_search(int *tree, int node, int depth, int height, int value) {
  printf("visited: %d\n", node);
  if (tree[node] == value)
    return node;
  if (depth == height - 1)
    return -1;
  else if (tree[node] > value)
    return BST_search(tree, 2 * node + 1, depth + 1, height, value);
  else
    return BST_search(tree, 2 * node + 2, depth + 1, height, value);
}

__uint32_t fix_bits(__uint32_t x, __uint32_t d) {
  assert(d <= 30);
  if (!d)
    return 1;
  __uint32_t y = (x << (32 - d)) >> (32 - d); // keep lower order d - 1 bits
  y |= (1UL << d);
  return y;
}

unsigned int hyperceil(unsigned int num) {
  unsigned int val = 1;
  unsigned int temp = num;
  while (temp != 1) {
    temp = temp >> 1;
    val = val << 1;
  }
  return (val == num) ? val : (val << 1);
}

int bfs_to_cache_oblivious(int node, int depth, int height) {
  if (height < 3) // if height lt 3, CO layout = BFS layout
    return node;
  __uint32_t h1, h2;
  __uint32_t h = (__uint32_t)height;
  __uint32_t d = (__uint32_t)depth;
  __uint32_t n = (__uint32_t)node;
  assert(h > 0);
  assert(__builtin_clz(h) < 31);
  h2 = hyperceil((h & 1) ? h / 2 + 1 : h / 2); // hyperceil(n) := ceil(log(n))
  h1 = h - h2;                                 // height of subtree A
  if (depth < h1)                              // if node is in subtree A
    return bfs_to_cache_oblivious(node, depth, h1);
  d -= h1; // depth of recursive case
  __uint32_t a =
      (h1 == 0) ? 1 : (1UL << h1) - 1; // number of nodes in subtree A
  __uint32_t b =
      (h2 == 0) ? 1 : (1UL << h2) - 1; // number of nodes in subtree Bi
  __uint32_t b_i =
      (d == 0) ? n : n >> d; // BFS index of node n at root of subtree Bi
  __uint32_t i = b_i - a;    // i of subtree Bi
  __uint32_t x = a + (i - 1) * b;
  __uint32_t _n = fix_bits(n, d);
  return x + bfs_to_cache_oblivious(_n, d, h2);
}

int BST_search_Cache_Oblivious(int *tree, int node, int depth, int height,
                               int value) {
  int CO_node = bfs_to_cache_oblivious(node + 1, depth, height) -
                1; // algorithm uses 1 indexing
  printf("visited: %d\n", CO_node);
  if (tree[CO_node] == value)
    return CO_node;
  if (depth == height - 1)
    return -1;
  else if (tree[CO_node] > value)
    return BST_search_Cache_Oblivious(tree, 2 * node + 1, depth + 1, height,
                                      value);
  else
    return BST_search_Cache_Oblivious(tree, 2 * node + 2, depth + 1, height,
                                      value);
}

int main() {
  int *array = (int *)malloc(ARRAY_SIZE * sizeof(int));
  int i;

  // Seed the random number generator
  srand(time(NULL));

  // Fill the array with random integers
  for (i = 0; i < ARRAY_SIZE; i++) {
    array[i] = rand();
  }
  int val = 1000000000;
  array[0] = val;

  // Sort the array
  qsort(array, ARRAY_SIZE, sizeof(int), compare_ints);
  int index = binary_search(array, val, 0, ARRAY_SIZE);
  printf("index: %d\n", index);

  int *arr = array;
  int n = ARRAY_SIZE;
  //   printf("Original Array: ");
  //   print_array(arr, n);

  TreeNode *root = sortedArrayToBST(arr, 0, n - 1);
  //   printTree(root, 0, 5);
  //   printf("tree height: %d\n", treeHeight(root));

  int *bfsArray = (int *)malloc(n * sizeof(int));
  BFS(root, bfsArray);
  //   printf("BFS Traversal Order: ");
  //   print_array(bfsArray, n);

  // put data in cache oblivious layout
  int *COArray = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    int COind = bfs_to_cache_oblivious(i + 1, (31 - __builtin_clz(i + 1)),
                                       treeHeight(root)) -
                1;
    COArray[COind] = bfsArray[i];
  }

  index = BST_search(bfsArray, 0, 0, treeHeight(root), val);
  printf("index: %d\n", index);
  index = BST_search_Cache_Oblivious(COArray, 0, 0, treeHeight(root), val);
  printf("index: %d\n", index);
  freeTree(root);
  free(array);
  free(bfsArray);
  free(COArray);
  return 0;
}