#include "tree.h"

static void _gatherNodesA(tree_A* t, int idx, char** arr, int* count, char* delStr);

// 연결 리스트 트리 노드를 후위 순회로 해제
static void _destroyLLNode(treenode* root);

// min값(후계자) 찾기
static treenode* _findMin(treenode* root);

// 연결 리스트 노드를 재귀적으로 삭제
static treenode* _deleteLL_recursive(treenode* root, char* str);

// 연결 리스트 트리 노드를 전위 순회로 배열 트리에 삽입
static void _preorderList2Array(treenode* root, tree_A* arr);

// 배열 트리를 전위 순회하며 연결 리스트 트리에 삽입
static void _preorderArray2List(tree_A* arr, int idx, tree_LL* list);

// 전위, 중위, 후위 방문 (배열 기반)
static void _preorderA(tree_A* t, int idx);
static void _inorderA(tree_A* t, int idx);
static void _postorderA(tree_A* t, int idx);

// 중위 순회로 n번째 노드를 찾기 (배열 기반)
static int _inorderCntA(tree_A* t, int idx, int* count, int num, char* result);

// 연결 리스트 기반 중위 순회 n번째 찾기
static int _inorderCntLL(treenode* root, int* count, int num, char* result);

// 연결 리스트 기반 전위/중위/후위 방문 재귀함수
static void _preorderLL(treenode* root);
static void _inorderLL(treenode* root);
static void _postorderLL(treenode* root);

static void _initQueue(Queue* q);
static int  _isEmpty(Queue* q);
static void _enqueue(Queue* q, treenode* node);
static treenode* _dequeue(Queue* q);
static void _levelorderLL(treenode* root);

// 배열 기반 BST에서 str의 인덱스 찾기
static int _findIndexA(tree_A* t, char* str);

/********************************************************************/
/********************     기존 함수 구현부      ********************/
/********************************************************************/

tree_A* CreateArrayTree()
{
    // 구조체 동적 할당
    tree_A* tree = (tree_A*)malloc(sizeof(tree_A));
    tree->maxindex = (int)pow(2, MAXDEGREE + 1);

    // 문자열 배열 동적 할당하고 ""로 초기화
    tree->data = (char**)malloc(sizeof(char*) * tree->maxindex);
    for (int i = 0; i < tree->maxindex; i++)
    {
        tree->data[i] = (char*)malloc(sizeof(char) * STRINGSIZE);
        strcpy(tree->data[i], "");
    }
    return tree;
}

tree_LL* CreateLListTree()
{
    tree_LL* tree = (tree_LL*)malloc(sizeof(tree_LL));
    tree->root = NULL;
    return tree;
}

// 배열 트리에 노드 삽입 (BST 규칙)
void InsertNodeA(tree_A* t, char* str)
{
    if (!t) return;

    // 루트(인덱스0)가 비어있다면 거기에 삽입
    if (strcmp(t->data[0], "") == 0)
    {
        strcpy(t->data[0], str);
        return;
    }

    // 루트가 있다면 내려가며 자리 찾기
    int idx = 0;
    while (1)
    {
        int cmp = strcmp(str, t->data[idx]);
        if (cmp < 0)
        {
            int left = 2 * idx + 1;
            if (left >= t->maxindex)
            {
                printf("트리가 꽉 차서 더 이상 삽입할 수 없습니다\n");
                return;
            }
            if (strcmp(t->data[left], "") == 0)
            {
                strcpy(t->data[left], str);
                return;
            }
            else
            {
                idx = left;
            }
        }
        else if (cmp > 0)
        {
            int right = 2 * idx + 2;
            if (right >= t->maxindex)
            {
                printf("트리가 꽉 차서 더 이상 삽입할 수 없습니다\n");
                return;
            }
            if (strcmp(t->data[right], "") == 0)
            {
                strcpy(t->data[right], str);
                return;
            }
            else
            {
                idx = right;
            }
        }
        else
        {
            // 중복은 삽입하지 않음
            printf("중복 데이터 [%s] 는 삽입하지 않습니다\n", str);
            return;
        }
    }
}

// 연결 리스트 트리에 노드 삽입 (BST 규칙)
static treenode* _insertLL_recursive(treenode* root, char* str)
{
    if (root == NULL)
    {
        treenode* newNode = (treenode*)malloc(sizeof(treenode));
        strcpy(newNode->data, str);
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    int cmp = strcmp(str, root->data);
    if (cmp < 0)
        root->left = _insertLL_recursive(root->left, str);
    else if (cmp > 0)
        root->right = _insertLL_recursive(root->right, str);
    else
        printf("중복 데이터 [%s] 는 삽입하지 않습니다\n", str);

    return root;
}

void InsertNodeLL(tree_LL* t, char* str)
{
    if (!t) return;
    t->root = _insertLL_recursive(t->root, str);
}

// 배열 트리 노드 삭제 - 재구축 방식
void DeleteNodeA(tree_A* t, char* str)
{
    if (!t) return;

    // 노드가 실제로 있는지 먼저 인덱스 찾기
    int idx = _findIndexA(t, str);
    if (idx == -1)
    {
        printf("[%s] 데이터가 트리에 없습니다\n", str);
        return;
    }

    // 전체 노드를 중위 순회하여, 삭제 대상이 아닌 노드만 모음
    char** nodeList = (char**)malloc(sizeof(char*) * (t->maxindex));
    for (int i = 0; i < t->maxindex; i++)
    {
        nodeList[i] = (char*)malloc(sizeof(char) * STRINGSIZE);
        strcpy(nodeList[i], "");
    }

    int count = 0;
    _gatherNodesA(t, 0, nodeList, &count, str);

    // 원본 트리의 데이터를 모두 ""로 리셋
    for (int i = 0; i < t->maxindex; i++)
    {
        strcpy(t->data[i], "");
    }

    // 모아둔 노드들을 재삽입 (삭제 노드는 제외됨)
    for (int i = 0; i < count; i++)
    {
        InsertNodeA(t, nodeList[i]);
    }

    // 임시 리스트 해제
    for (int i = 0; i < t->maxindex; i++)
        free(nodeList[i]);
    free(nodeList);

    printf("[%s] 노드를 배열 기반 트리에서 삭제했습니다\n", str);
}

// 연결 리스트 트리 노드 삭제 (정석 BST 삭제)
void DeleteNodeLL(tree_LL* t, char* str)
{
    if (!t) return;
    t->root = _deleteLL_recursive(t->root, str);
}

// 연결 리스트 -> 배열 트리 변환
tree_A* List2Array(tree_LL* t)
{
    if (!t) return NULL;
    tree_A* arrTree = CreateArrayTree();
    _preorderList2Array(t->root, arrTree);
    return arrTree;
}

// 배열 트리 -> 연결 리스트 트리 변환
tree_LL* Array2List(tree_A* t)
{
    if (!t) return NULL;
    tree_LL* listTree = CreateLListTree();
    _preorderArray2List(t, 0, listTree);
    return listTree;
}

// 배열 트리 순회 출력
// type 0: Preorder, 1: Inorder, 2: Postorder, 3: Levelorder
void PrintNodeA(tree_A* t, int type)
{
    if (!t) return;
    switch (type)
    {
    case 0:
        _preorderA(t, 0);
        break;
    case 1:
        _inorderA(t, 0);
        break;
    case 2:
        _postorderA(t, 0);
        break;
    case 3:
        for (int i = 0; i < t->maxindex; i++)
            if (strcmp(t->data[i], "") != 0)
                printf("%s ", t->data[i]);
        break;
    }
    printf("\n");
}

// 연결 리스트 트리 순회 출력
void PrintNodeLL(tree_LL* t, int type)
{
    if (!t || !t->root) return;
    switch (type)
    {
    case 0:
        _preorderLL(t->root);
        break;
    case 1:
        _inorderLL(t->root);
        break;
    case 2:
        _postorderLL(t->root);
        break;
    case 3:
        _levelorderLL(t->root);
        break;
    }
    printf("\n");
}

// 포화/완전/편향/일반 이진트리 체크하기 (배열)
static int _countNodesA(tree_A* t, int idx)
{
    if (idx >= t->maxindex) return 0;
    if (strcmp(t->data[idx], "") == 0) return 0;
    return 1 + _countNodesA(t, 2 * idx + 1) + _countNodesA(t, 2 * idx + 2);
}

static int _heightA(tree_A* t, int idx)
{
    if (idx >= t->maxindex) return 0;
    if (strcmp(t->data[idx], "") == 0) return 0;
    int hl = _heightA(t, 2 * idx + 1);
    int hr = _heightA(t, 2 * idx + 2);
    return (hl > hr ? hl : hr) + 1;
}

void CheckBSTA(tree_A* t)
{
    if (!t) return;
    int nodeCount = _countNodesA(t, 0);
    int h = _heightA(t, 0);

    // 2^h - 1 == nodeCount 이면 포화 이진트리라 가정
    if ((int)pow(2, h) - 1 == nodeCount)
    {
        printf("1. 포화 이진트리 입니다\n");
        return;
    }

    // 편향 여부 간단 체크 (왼쪽 서브트리 or 오른쪽 서브트리만 존재?)
    int leftCount = _countNodesA(t, 1);
    int rightCount = _countNodesA(t, 2);
    if (leftCount == 0 || rightCount == 0)
    {
        printf("3. 편향 이진트리 입니다\n");
        return;
    }

    // 일단 완전 이진트리(또는 일반 이진트리)라고 출력
    printf("2. 완전 이진트리(또는 일반 이진트리) 입니다\n");
}

// 포화/완전/편향/일반 이진트리 체크하기 (연결 리스트)
static int _countNodesLL(treenode* root)
{
    if (!root) return 0;
    return 1 + _countNodesLL(root->left) + _countNodesLL(root->right);
}

static int _heightLL(treenode* root)
{
    if (!root) return 0;
    int hl = _heightLL(root->left);
    int hr = _heightLL(root->right);
    return (hl > hr ? hl : hr) + 1;
}

void CheckBSTLL(tree_LL* t)
{
    if (!t || !t->root) return;
    int nodeCount = _countNodesLL(t->root);
    int h = _heightLL(t->root);

    if ((int)pow(2, h) - 1 == nodeCount)
    {
        printf("1. 포화 이진트리 입니다\n");
        return;
    }

    // 편향 여부 간단 체크
    treenode* cur = t->root;
    int leftOnly = 1;
    int rightOnly = 1;
    while (cur)
    {
        if (cur->left && cur->right)
        {
            leftOnly = 0;
            rightOnly = 0;
            break;
        }
        if (cur->left)
            cur = cur->left;
        else if (cur->right)
            cur = cur->right;
        else
            break;
    }
    if (leftOnly || rightOnly)
    {
        printf("3. 편향 이진트리 입니다\n");
        return;
    }

    printf("2. 완전 이진트리(또는 일반 이진트리) 입니다\n");
}

// n번째 노드 찾기 (배열)
char* FindnthA(tree_A* t, int num)
{
    if (!t) return NULL;
    static char result[STRINGSIZE];
    int count = 0;
    if (_inorderCntA(t, 0, &count, num, result))
        return result;
    return NULL;
}

// n번째 노드 찾기 (연결 리스트)
char* FindnthLL(tree_LL* t, int num)
{
    if (!t || !t->root) return NULL;
    static char result[STRINGSIZE];
    int count = 0;
    if (_inorderCntLL(t->root, &count, num, result))
        return result;
    return NULL;
}

// 배열 트리에서 경로 찾기
void FindPathA(tree_A* t, char* str)
{
    if (!t) return;

    int idx = 0;
    char path[1024] = { 0 };
    while (idx < t->maxindex && strcmp(t->data[idx], "") != 0)
    {
        int cmp = strcmp(str, t->data[idx]);
        if (cmp == 0)
        {
            printf("찾는 과정: %s\n", path[0] == '\0' ? "(루트)" : path);
            return;
        }
        else if (cmp < 0)
        {
            strcat(path, "L");
            idx = 2 * idx + 1;
        }
        else
        {
            strcat(path, "R");
            idx = 2 * idx + 2;
        }
    }
    printf("데이터가 없습니다\n");
}

// 연결 리스트 트리에서 경로 찾기
static void _findPathLL_recursive(treenode* root, char* str, char* path, int* found)
{
    if (!root || *found) return;

    int cmp = strcmp(str, root->data);
    if (cmp == 0)
    {
        printf("찾는 과정: %s\n", path[0] == '\0' ? "(루트)" : path);
        *found = 1;
        return;
    }
    else if (cmp < 0)
    {
        char newPath[1024];
        sprintf(newPath, "%s%s", path, (path[0] == '\0') ? "L" : "L");
        _findPathLL_recursive(root->left, str, newPath, found);
    }
    else
    {
        char newPath[1024];
        sprintf(newPath, "%s%s", path, (path[0] == '\0') ? "R" : "R");
        _findPathLL_recursive(root->right, str, newPath, found);
    }
}

void FindPathLL(tree_LL* t, char* str)
{
    if (!t || !t->root)
    {
        printf("데이터가 없습니다\n");
        return;
    }
    int found = 0;
    _findPathLL_recursive(t->root, str, "", &found);
    if (!found)
        printf("데이터가 없습니다\n");
}

// 배열 트리 해제
void DestroyArrayTree(tree_A* t)
{
    if (!t) return;
    for (int i = 0; i < t->maxindex; i++)
    {
        free(t->data[i]);
    }
    free(t->data);
    free(t);
}

// 연결 리스트 트리 해제
void DestroyLListTree(tree_LL* t)
{
    if (!t) return;
    _destroyLLNode(t->root);
    free(t);
}
/********************************************************************/
/********************  아래부터 추가 함수 구현부  ********************/
/********************************************************************/

// 배열 기반 트리 노드를 모두 수집하기 위한 재귀함수 (삭제할 str은 제외)
static void _gatherNodesA(tree_A* t, int idx, char** arr, int* count, char* delStr)
{
    // 인덱스 범위 벗어나면 리턴
    if (idx >= t->maxindex) return;

    // 현재 인덱스가 빈 문자열이면 노드가 없으므로 리턴
    if (strcmp(t->data[idx], "") == 0) return;

    // 왼쪽 서브트리 수집
    _gatherNodesA(t, 2 * idx + 1, arr, count, delStr);

    // 현재 노드가 삭제 대상(delStr)이 아니면 배열에 수집
    if (strcmp(t->data[idx], delStr) != 0)
    {
        strcpy(arr[*count], t->data[idx]);
        (*count)++;
    }

    // 오른쪽 서브트리 수집
    _gatherNodesA(t, 2 * idx + 2, arr, count, delStr);
}

// 연결 리스트 트리 노드를 후위 순회로 해제
static void _destroyLLNode(treenode* root)
{
    if (!root) return;
    _destroyLLNode(root->left);
    _destroyLLNode(root->right);
    free(root);
}

// min값(후계자) 찾기
static treenode* _findMin(treenode* root)
{
    while (root && root->left != NULL)
        root = root->left;
    return root;
}

// 연결 리스트 노드를 재귀적으로 삭제
static treenode* _deleteLL_recursive(treenode* root, char* str)
{
    if (root == NULL)
    {
        printf("[%s] 데이터가 트리에 없습니다\n", str);
        return NULL;
    }

    int cmp = strcmp(str, root->data);
    if (cmp < 0)
        root->left = _deleteLL_recursive(root->left, str);
    else if (cmp > 0)
        root->right = _deleteLL_recursive(root->right, str);
    else
    {
        // 자식이 없는 경우
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        // 왼쪽만 있는 경우
        else if (root->right == NULL)
        {
            treenode* temp = root->left;
            free(root);
            return temp;
        }
        // 오른쪽만 있는 경우
        else if (root->left == NULL)
        {
            treenode* temp = root->right;
            free(root);
            return temp;
        }
        // 자식이 둘 다 있는 경우 -> 후계자 찾아 교체
        else
        {
            treenode* successor = _findMin(root->right);
            strcpy(root->data, successor->data);
            root->right = _deleteLL_recursive(root->right, successor->data);
        }
    }
    return root;
}

// 연결 리스트 트리 노드를 전위 순회로 배열 트리에 삽입
static void _preorderList2Array(treenode* root, tree_A* arr)
{
    if (!root) return;
    InsertNodeA(arr, root->data);
    _preorderList2Array(root->left, arr);
    _preorderList2Array(root->right, arr);
}

// 배열 트리를 전위 순회하며 연결 리스트 트리에 삽입
static void _preorderArray2List(tree_A* arr, int idx, tree_LL* list)
{
    if (idx >= arr->maxindex) return;
    if (strcmp(arr->data[idx], "") == 0) return;

    InsertNodeLL(list, arr->data[idx]);
    _preorderArray2List(arr, 2 * idx + 1, list);
    _preorderArray2List(arr, 2 * idx + 2, list);
}

// 전위/중위/후위 방문을 위한 내부 재귀함수 (배열 기반)
static void _preorderA(tree_A* t, int idx)
{
    if (idx >= t->maxindex) return;
    if (strcmp(t->data[idx], "") == 0) return;

    printf("%s ", t->data[idx]);
    _preorderA(t, 2 * idx + 1);
    _preorderA(t, 2 * idx + 2);
}

static void _inorderA(tree_A* t, int idx)
{
    if (idx >= t->maxindex) return;
    if (strcmp(t->data[idx], "") == 0) return;

    _inorderA(t, 2 * idx + 1);
    printf("%s ", t->data[idx]);
    _inorderA(t, 2 * idx + 2);
}

static void _postorderA(tree_A* t, int idx)
{
    if (idx >= t->maxindex) return;
    if (strcmp(t->data[idx], "") == 0) return;

    _postorderA(t, 2 * idx + 1);
    _postorderA(t, 2 * idx + 2);
    printf("%s ", t->data[idx]);
}

// 중위 순회로 n번째 노드를 찾기 (배열 기반)
static int _inorderCntA(tree_A* t, int idx, int* count, int num, char* result)
{
    if (idx >= t->maxindex) return 0;
    if (strcmp(t->data[idx], "") == 0) return 0;

    if (_inorderCntA(t, 2 * idx + 1, count, num, result))
        return 1;

    (*count)++;
    if (*count == num)
    {
        strcpy(result, t->data[idx]);
        return 1;
    }

    if (_inorderCntA(t, 2 * idx + 2, count, num, result))
        return 1;

    return 0;
}

// 연결 리스트 기반 중위 순회 n번째 찾기
static int _inorderCntLL(treenode* root, int* count, int num, char* result)
{
    if (!root) return 0;

    if (_inorderCntLL(root->left, count, num, result))
        return 1;

    (*count)++;
    if (*count == num)
    {
        strcpy(result, root->data);
        return 1;
    }

    if (_inorderCntLL(root->right, count, num, result))
        return 1;

    return 0;
}

// 연결 리스트 기반 전위/중위/후위 방문 재귀함수
static void _preorderLL(treenode* root)
{
    if (!root) return;
    printf("%s ", root->data);
    _preorderLL(root->left);
    _preorderLL(root->right);
}

static void _inorderLL(treenode* root)
{
    if (!root) return;
    _inorderLL(root->left);
    printf("%s ", root->data);
    _inorderLL(root->right);
}

static void _postorderLL(treenode* root)
{
    if (!root) return;
    _postorderLL(root->left);
    _postorderLL(root->right);
    printf("%s ", root->data);
}

static void _initQueue(Queue* q)
{
    q->front = 0;
    q->rear = 0;
}

static int _isEmpty(Queue* q)
{
    return (q->front == q->rear);
}

static void _enqueue(Queue* q, treenode* node)
{
    q->data[q->rear++] = node;
}

static treenode* _dequeue(Queue* q)
{
    return q->data[q->front++];
}

static void _levelorderLL(treenode* root)
{
    if (!root) return;

    Queue q;
    _initQueue(&q);
    _enqueue(&q, root);

    while (!_isEmpty(&q))
    {
        treenode* cur = _dequeue(&q);
        printf("%s ", cur->data);
        if (cur->left) _enqueue(&q, cur->left);
        if (cur->right) _enqueue(&q, cur->right);
    }
}

// 배열 기반 BST에서 str의 인덱스 찾기
static int _findIndexA(tree_A* t, char* str)
{
    int idx = 0;
    while (idx < t->maxindex && strcmp(t->data[idx], "") != 0)
    {
        int cmp = strcmp(str, t->data[idx]);
        if (cmp == 0) return idx;
        else if (cmp < 0) idx = 2 * idx + 1;
        else idx = 2 * idx + 2;
    }
    return -1;
}