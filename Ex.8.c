#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left, *right;
} Node;

Node* newNode(int data);
Node* insert(Node* root, int data);
void inorder(Node *temp);
Node* deleteNode(Node* root, int data);
int search(Node* root, int data);

int main() {
    Node* root = NULL;
    int choice, data;
    while(1) {
        printf("\n1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter the value to be inserted: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Enter the value to be deleted: ");
                scanf("%d", &data);
                root = deleteNode(root, data);
                break;
            case 3:
                printf("Enter the value to be searched: ");
                scanf("%d", &data);
                if(search(root, data) == 1)
                    printf("%d found in the tree\n", data);
                else
                    printf("%d not found in the tree\n", data);
                break;
            case 4:
                inorder(root);
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice, try again\n");
        }
    }
    return 0;
}

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

Node* insert(Node* root, int data) {
    if(root == NULL) {
        root = newNode(data);
    }
    else if(data <= root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

void inorder(Node *temp) {
    if(temp == NULL)
        return;
    inorder(temp->left);
    printf("%d -> ", temp->data);
    inorder(temp->right);
}

Node* deleteNode(Node* root, int data) {
    if(root == NULL)
        return root;
    if(data < root->data)
        root->left = deleteNode(root->left, data);
    else if(data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if(root->left == NULL) {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL) {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        root->data = minValue(root->right);
        root->right = deleteNode(root->right, root->data);
    }
    return root;
}

int minValue(Node* temp) {
    int minv = temp->data;
    while(temp->left != NULL) {
        minv = temp->left->data;
        temp = temp->left;
    }
    return minv;
}

int search(Node* root, int data) {
    if(root == NULL || root->data == data)
        return root != NULL;
    if(root->data < data)
        return search(root->right, data);
    return search(root->left, data);
}
