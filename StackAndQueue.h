#pragma once
struct Node
{
	char* data;
	Node* pNext;
};

struct Stack
{
	Node* pHead;
	Node* pTail;
};

struct Queue
{
	Node* pHead;
	Node* pTail;
};

void KhoiTao(Queue& queue);
void KhoiTao(Stack& stack);
Node* TaoNode(char* data);
void XoaNode(Node* node);
void Enqueue(Queue& queue, Node* node);
Node* Dequeue(Queue& queue);
void Push(Stack& stack, Node* node);
Node* Pop(Stack& stack);
