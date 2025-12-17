#include<stdio.h>
#include<string.h>
#include"StackAndQueue.h"

void KhoiTao(Queue& queue)
{
	queue.pHead = NULL;
	queue.pTail = NULL;
}

void KhoiTao(Stack& stack)
{
	stack.pHead = NULL;
	stack.pTail = NULL;
}

Node* TaoNode(char* data)
{
	Node* node = new Node;

	int len = strlen(data);
	node->data = new char[len + 1];
	strcpy_s(node->data, len + 1, data);

	node->pNext = NULL;
	return node;
}

void XoaNode(Node* node)
{
	delete[] node->data;
	delete node;
}

void Enqueue(Queue& queue, Node* node)
{
	if (queue.pHead == NULL)
	{
		queue.pHead = node;
		queue.pTail = node;
	}
	else
	{
		queue.pTail->pNext = node;
		queue.pTail = node;
	}
}

Node* Dequeue(Queue& queue)
{
	Node* node = queue.pHead;
	if (queue.pHead != NULL)
	{
		queue.pHead = queue.pHead->pNext;
		if (queue.pHead == NULL)
		{
			queue.pTail = NULL;
		}

		node->pNext = NULL;
	}
	return node;
}

void Push(Stack& stack, Node* node)
{
	if (stack.pHead == NULL)
	{
		stack.pHead = node;
		stack.pTail = node;
	}
	else
	{
		node->pNext = stack.pHead;
		stack.pHead = node;
	}
}

Node* Pop(Stack& stack)
{
	Node* node = stack.pHead;
	if (stack.pHead != NULL)
	{
		stack.pHead = stack.pHead->pNext;
		if (stack.pHead == NULL)
		{
			stack.pTail = NULL;
		}

		node->pNext = NULL;
	}
	return node;
}