#include<stdio.h>
#include<string.h>	
#include"TinhToanSoLon.h"

//Hàm so sánh 2 số ko âm
int SoSanhSoDuong(char* a, char* b)
{
	int lenA = strlen(a);
	int lenB = strlen(b);
	if (lenA > lenB) return 1;
	if (lenA < lenB) return -1;
	return strcmp(a, b);
}

//Hàm cộng 2 số dương
void CongSoDuong(char* a, char* b, char* kq)
{
	int lenA = strlen(a);
	int lenB = strlen(b);
	int carry = 0, sum;
	char temp[MAX];

	int i = lenA - 1, j = lenB - 1, k = 0;
	while (i >= 0 || j >= 0 || carry != 0)
	{
		sum = carry;
		if (i >= 0)
		{
			sum = sum + a[i--] - '0';
		}
		if (j >= 0)
		{
			sum = sum + b[j--] - '0';
		}
		temp[k++] = sum % 10 + '0';
		carry = sum / 10;
	}
	temp[k] = '\0';

	//loại bỏ số 0 ở đầu kết quá VD: 080100 -> 0801
	//Hàm này có tác dụng loại bỏ số 0 trong HamNhan với trường hợp truyền vào hàm 1 chuỗi rỗng
	while (k > 1 && temp[k - 1] == '0') k--;
	temp[k] = '\0';

	//đảo ngược số lại VD: temp[MAX] = "0801" -> kq[MAX] = "1080"
	for (int m = 0; m < k; m++)
	{
		kq[m] = temp[k - m - 1];
	}
	kq[k] = '\0';
}

//Hàm trừ 2 số dương với điều kiện a>=b
void TruSoDuong(char* a, char* b, char* kq)
{
	int lenA = strlen(a);
	int lenB = strlen(b);
	int muon = 0, hieu;
	char temp[MAX];

	int i = lenA - 1, j = lenB - 1, k = 0;
	while (i >= 0)
	{
		hieu = a[i] - '0' - muon;
		if (j >= 0)
		{
			hieu = hieu - (b[j--] - '0');
		}
		if (hieu < 0)
		{
			hieu = hieu + 10;
			muon = 1;
		}
		else
		{
			muon = 0;
		}

		temp[k++] = hieu + '0';
		i--;
	}

	//loại bỏ số 0 ở đầu kết quá VD: 080100 -> 0801
	while (k > 1 && temp[k - 1] == '0') k--;
	temp[k] = '\0';

	//đảo chuỗi kết quả
	for (int m = 0; m < k; m++)
	{
		kq[m] = temp[k - m - 1];
	}
	kq[k] = '\0';
}

void HamCong(char* a, char* b, char* kq)
{
	int aLaSoAm = (a[0] == '-');
	int bLaSoAm = (b[0] == '-');

	//lấy giá trị tuyệt đối
	char absA[MAX], absB[MAX];
	//Nếu là số âm thì trỏ đến phần tử thứ 1, ngược lại nếu ko là số âm thì trỏ đến phần tử thứ 0
	strcpy_s(absA, aLaSoAm ? a + 1 : a);
	strcpy_s(absB, bLaSoAm ? b + 1 : b);

	//Nếu a và b cùng dấu thì thực hiện phép cộng trị tuyệt đối
	if (aLaSoAm == bLaSoAm)
	{
		CongSoDuong(absA, absB, kq);
		//Nếu cả 2 đều là số âm thì thêm dấu âm vào kq
		if (aLaSoAm)
		{
			char temp[MAX];
			sprintf_s(temp, MAX, "-%s", kq);
			strcpy_s(kq, MAX, temp);
		}
	}
	else//Ngược lại a và b khác dấu
	{
		//Khác dấu thì thực hiện phép trừ
		int ss = SoSanhSoDuong(absA, absB);
		//Nếu ss >=0 có nghĩa là số a >= số b
		if (ss >= 0)
		{
			TruSoDuong(absA, absB, kq);
			//Dấu của kq là âm nếu a là số âm
			if (aLaSoAm)
			{
				char temp[MAX];
				sprintf_s(temp, MAX, "-%s", kq);
				strcpy_s(kq, MAX, temp);
			}
		}
		else//Ngược lại a<b
		{
			TruSoDuong(absB, absA, kq);
			//Dấu của kq là âm nếu b là số âm
			if (bLaSoAm)
			{
				char temp[MAX];
				sprintf_s(temp, MAX, "-%s", kq);
				strcpy_s(kq, MAX, temp);
			}
		}
	}
}

void HamTru(char* a, char* b, char* kq)
{
	int aLaSoAm = (a[0] == '-');
	int bLaSoAm = (b[0] == '-');

	//lấy giá trị tuyệt đối
	char absA[MAX], absB[MAX];
	//Nếu là số âm thì trỏ đến phần tử thứ 1, ngược lại nếu ko là số âm thì trỏ đến phần tử thứ 0
	strcpy_s(absA, aLaSoAm ? a + 1 : a);
	strcpy_s(absB, bLaSoAm ? b + 1 : b);

	//Nếu cùng dấu thì thực hiện phép trừ trị tuyệt đối
	if (aLaSoAm == bLaSoAm)
	{
		int ss = SoSanhSoDuong(a, b);
		//Nếu ss >=0 có nghĩa là a >= b
		if (ss >= 0)
		{
			TruSoDuong(absA, absB, kq);
			//Dấu của kq là âm nếu a là số âm và kq != 0
			if (aLaSoAm && strcmp(kq, "0") != 0)
			{
				char temp[MAX];
				sprintf_s(temp, MAX, "-%s", kq);
				strcpy_s(kq, MAX, temp);
			}
		}
		else//Ngược lại a<b
		{
			TruSoDuong(absB, absA, kq);
			//Nếu a dương và nhỏ hơn b, kết quả sẽ âm. Lúc này dấu sẽ phụ thuộc vào số lớn, (-a) - (-b)= b-a lúc này b biến thành số duong nên phải có phủ định ở khúc này 
			if (!bLaSoAm)
			{
				char temp[MAX];
				sprintf_s(temp, MAX, "-%s", kq);
				strcpy_s(kq, MAX, temp);
			}
		}
	}
	else//Ngược lại khác dấu thực hiện phép cộng trị tuyệt đối
	{
		CongSoDuong(absA, absB, kq);
		//Dấu của kq là âm nếu a là số âm
		if (aLaSoAm)
		{
			char temp[MAX];
			sprintf_s(temp, MAX, "-%s", kq);
			strcpy_s(kq, MAX, temp);
		}
	}
}

// Hàm nhân một chuỗi số lớn dương với một chữ số
void NhanMotSoDuong(char* a, char c, char* kq)
{
	int lenA = strlen(a);
	int carry = 0, nhan;
	int digit = c - '0';
	char temp[MAX];

	int i = lenA - 1, k = 0;
	while (i >= 0)
	{
		nhan = (a[i--] - '0') * digit + carry;
		temp[k++] = nhan % 10 + '0';
		carry = nhan / 10;
	}

	if (carry != 0)
	{
		temp[k++] = carry + '0';
	}
	temp[k] = '\0';

	// Đảo ngược chuỗi kết quả
	for (int m = 0; m < k; m++)
	{
		kq[m] = temp[k - m - 1];
	}
	kq[k] = '\0';
}

void HamNhan(char* a, char* b, char* kq)
{
	//a*b
	int aLaSoAm = (a[0] == '-');
	int bLaSoAm = (b[0] == '-');

	//lấy giá trị tuyệt đối
	char absA[MAX], absB[MAX];
	//Nếu là số âm thì trỏ đến phần tử thứ 1, ngược lại nếu ko là số âm thì trỏ đến phần tử thứ 0
	strcpy_s(absA, aLaSoAm ? a + 1 : a);
	strcpy_s(absB, bLaSoAm ? b + 1 : b);

	//kiểm tra xem a hay b có số nào bằng không hay ko
	if (strcmp(absA, "0") == 0 || strcmp(absB, "0") == 0)
	{
		strcpy_s(kq, MAX, "0");
		return;
	}

	strcpy_s(kq, MAX, "0");

	//nhân từng số của b với a rồi cộng lại, mỗi số sẽ tăng lên 1 số 0 ở phía sau mỗi khi nhân xong
	int lenB = strlen(absB);
	for (int i = lenB - 1; i >= 0; i--)
	{
		char temp[MAX];
		NhanMotSoDuong(absA, absB[i], temp);

		//thêm số 0 vào đằng sau
		int lenTemp = strlen(temp);
		for (int j = 0; j < lenB - 1 - i; j++)
		{
			temp[lenTemp + j] = '0';
		}
		temp[lenTemp + lenB - 1 - i] = '\0';

		//cộng temp vào kq
		//trong hàm cộng có khử số không khi nhân với không
		HamCong(kq, temp, kq);//cẩn thận vì có thể trong hàm cộng tác động trực tiếp tới biến kq nếu có lỗi có thể xử dụng câu lệnh dưới

		/*
		char temp2[MAX];
		HamCong(kq, temp, temp2);
		strcpy_s(kq,MAX, temp2);*/
	}

	//Nếu 2 số khác dấu nhau có nghĩa là có 1 số đang có dấu âm
	if (aLaSoAm != bLaSoAm && strcmp(kq, "0") != 0)
	{
		char temp[MAX];
		sprintf_s(temp, "-%s", kq);
		strcpy_s(kq, MAX, temp);
	}
}

void HamChia(char* a, char* b, char* kq)
{
	//a/b
	int aLaSoAm = (a[0] == '-');
	int bLaSoAm = (b[0] == '-');

	//lấy giá trị tuyệt đối
	char absA[MAX], absB[MAX];
	//Nếu là số âm thì trỏ đến phần tử thứ 1, ngược lại nếu ko là số âm thì trỏ đến phần tử thứ 0
	strcpy_s(absA, aLaSoAm ? a + 1 : a);
	strcpy_s(absB, bLaSoAm ? b + 1 : b);

	//kiểm tra xem a có lớn hơn hoặc bằng b hay ko
	if (SoSanhSoDuong(a, b) < 0)
	{
		strcpy_s(kq, MAX, "0");
		//dư sẽ là số a, sau này có thể cái tiến tại dây để lấy dư
		return;
	}

	//lấy từng số của absA đưa và dư để xem dư-abs >=0 hay ko nếu ko thì tiếp tục thêm vào
	//VD:số a = 1234, b=40, dư = 0
	//đưa số đầu tiên vào là số 1 => dư = 01 (ko cần quan tâm số 0 đằng trước vì sẽ dc khử ở trong hàm TruSoDuong)
	//thấy dư= 01 trừ 40 chưa >= 0, tiếp tục đưa số thứ 2 vào dư = 012
	int lenA = strlen(absA);
	char du[MAX] = "0";//dư số dư sẽ nằm trong chuỗi này có thể cải tiến tại dây để lấy dư
	int i;
	for (i = 0; i < lenA; i++)
	{
		int lenDu = strlen(du);
		du[lenDu] = absA[i];
		du[lenDu + 1] = '\0';

		//loại bỏ các số dư ở dầu
		int k = 0;
		while (du[k] == '0' && du[k + 1] != '\0') k++;
		int j;
		for (j = 0; j < strlen(du) - k; j++)
		{
			du[j] = du[k + j];
		}
		du[j] = '\0';

		//Tìm chữ số của thương
		int count = 0;
		while (SoSanhSoDuong(du, absB) >= 0)
		{
			HamTru(du, absB, du);//cẩn thận vì có thể trong hàm trừ tác động trực tiếp tới biến kq nếu có lỗi có thể xử dụng câu lệnh dưới

			/*
			char temp[MAX];
			HamTru(du, absB, temp);
			strcpy_s(du, temp);*/

			count++;
		}
		//thêm chữ số của thương vào kết quả
		kq[i] = count + '0';
	}
	kq[i] = '\0';

	//Loại bỏ số 0 ở đầu của thương
	int k = 0;
	while (kq[k] == '0' && kq[k + 1] != '\0') k++;

	int j;
	for (j = 0; j < i - k; j++)
	{
		kq[j] = kq[k + j];
	}
	kq[j] = '\0';

	if (aLaSoAm != bLaSoAm && strcmp(kq, "0") != 0)
	{
		char temp[MAX];
		sprintf_s(temp, "-%s", kq);
		strcpy_s(kq, MAX, temp);
	}
}

