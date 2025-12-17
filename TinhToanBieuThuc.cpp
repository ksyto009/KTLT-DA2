#include<stdio.h>
#include<string.h>
#include"TinhToanSoLon.h"
#include"TinhToanBieuThuc.h"
#include"XuLyTapTin.h"

bool LaChuSo(char c)
{
	return c >= '0' && c <= '9';
}

bool LaToanTu(char c)
{
	return c == '+' || c == '-' || c == '*' || c == ':';
}

int ToanTuUuTien(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == ':') return 2;
	return 0;
}

Queue ChuyenTrungToSangHauTo(char* trungTo)
{
	XoaKhoangTrang(trungTo);
	Queue queue;
	KhoiTao(queue);
	Stack stack;
	KhoiTao(stack);

	int i = 0;
	while (trungTo[i] != '\0' && trungTo[i] != '\n')
	{
		if (LaChuSo(trungTo[i]) || (trungTo[i] == '-' && trungTo[i - 1] != ')' && !LaChuSo(trungTo[i - 1]))) //Nếu là số đưa số vào queue
		{
			char temp[MAX];
			int j = 0;
			while (LaChuSo(trungTo[i]) || (trungTo[i] == '-' && trungTo[i - 1] != ')' && !LaChuSo(trungTo[i - 1])))
			{
				temp[j++] = trungTo[i++];
			}
			temp[j] = '\0';

			Node* node = TaoNode(temp);

			Enqueue(queue, node);

		}
		else if (trungTo[i] == '(') //Nếu là '(' thì đưa vào stack
		{
			char temp[2] = { trungTo[i],'\0' };
			Node* node = TaoNode(temp);
			Push(stack, node);
			i++;
		}
		else if (trungTo[i] == ')') //Nếu là ')' thì lấy các phần tử trong stack ra đưa vào queue cho đến khi nào gặp ')'. Sau đó xóa ')'
		{
			Node* node;
			while (stack.pHead != NULL && strcmp(stack.pHead->data, "(") != 0)
			{
				node = Pop(stack);
				Enqueue(queue, node);
			}
			//xóa dấu '('
			node = Pop(stack);
			XoaNode(node);
			i++;
		}
		else //Nếu là toán tử 
		{
			char temp[2] = { trungTo[i],'\0' };
			Node* node = TaoNode(temp);
			//Nếu phần tử đầu tiên của stack là toán tử, toán tử đang xét nhỏ hơn toán tử trong stack thì lấy phần tử trong stack ra đưa vào queue
			while (stack.pHead != NULL && LaToanTu(stack.pHead->data[0]) && ToanTuUuTien(stack.pHead->data[0]) >= ToanTuUuTien(temp[0]))
			{
				Node* nodeTemp = Pop(stack);
				Enqueue(queue, nodeTemp);
			}

			Push(stack, node);//đưa toán tử vào stack
			i++;
		}
	}

	while (stack.pHead != NULL)
	{
		Node* node = Pop(stack);
		Enqueue(queue, node);
	}

	return queue;
}

void TinhToan(char* a, char* b, char op, char* kq)
{
	if (op == '+') HamCong(a, b, kq);
	else if (op == '-') HamTru(a, b, kq);
	else if (op == '*') HamNhan(a, b, kq);
	else if (op == ':') HamChia(a, b, kq);
}

void TinhToanHauTo(Queue& queue, char* kq)
{
	Stack stack;
	KhoiTao(stack);

	while (queue.pHead != NULL)
	{
		Node* node = Dequeue(queue);
		//Nếu là số

		if (LaChuSo(node->data[0]) || (node->data[0] == '-' && LaChuSo(node->data[1])))
		{
			Push(stack, node);
		}
		else//Ngược lại là toán tử thì lấy hai số từ ngăn xếp, tính toán và đẩy kết quả vào ngăn xếp
		{
			Node* op2 = Pop(stack);
			Node* op1 = Pop(stack);

			int lenTemp = strlen(op1->data) + strlen(op2->data);
			char temp[MAX];
			TinhToan(op1->data, op2->data, node->data[0], temp);

			Node* nodeKq = TaoNode(temp);
			Push(stack, nodeKq);

			XoaNode(op1);
			XoaNode(op2);
			XoaNode(node);
		}
	}

	//kq cuối cùng là phần tử duy nhất trong stack
	Node* node = Pop(stack);
	strcpy_s(kq, MAX, node->data);
	XoaNode(node);
}