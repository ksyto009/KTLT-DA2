#include<stdio.h>
#include<string.h>
#include"StackAndQueue.h"
#include"TinhToanBieuThuc.h"
#include"TinhToanSoLon.h"

void XoaKhoangTrang(char* str)
{
	int i, j = 0;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ')
		{
			str[j++] = str[i];
		}
	}
	str[j] = '\0';

	/*
	char kq[MAX * 5] = "";
	char* token;
	char* nextToken = NULL;
	token = strtok_s(str, " ", &nextToken);

	while (token != NULL)
	{
		strcat_s(kq, token);
		token = strtok_s(NULL, " ", &nextToken);
	}
	strcpy_s(str, MAX * 5, kq);*/
}

void DocVaGhiFile(const char* input, const char* output)
{
	FILE* fileInput;
	FILE* fileOutput;
	fopen_s(&fileInput, input, "rt");
	fopen_s(&fileOutput, output, "wt");
	if (fileInput == NULL || fileOutput == NULL)
	{
		printf("Khong the mo file\n");
		return;
	}

	char trungTo[MAX * 5];
	while (fgets(trungTo, MAX * 5, fileInput) != NULL)
	{
		printf("Bieu thuc trung to la: %s", trungTo);
		Queue queue;
		queue = ChuyenTrungToSangHauTo(trungTo);
		Node* node = queue.pHead;
		printf("Bieu thuc hau to la: ");
		while (node != NULL)
		{
			printf("%s ", node->data);
			node = node->pNext;
		}
		printf("\n");

		char kq[MAX];
		TinhToanHauTo(queue, kq);
		printf("kq qua cua bieu thuc phia tren la: %s\n", kq);
		printf("\n");

		fprintf(fileOutput, "%s\n", kq);
	}
}