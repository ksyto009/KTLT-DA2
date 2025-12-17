#pragma once
#include"StackAndQueue.h"

bool LaChuSo(char c);
bool LaToanTu(char c);
int ToanTuUuTien(char op);
Queue ChuyenTrungToSangHauTo(char* trungTo);
void TinhToan(char* a, char* b, char op, char* kq);
void TinhToanHauTo(Queue& queue, char* kq);
