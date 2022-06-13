int Mmain(API Api, LPCWSTR PasswdFromExecute){
	char msg[] = {'H','e','l','l','o',' ','w','o','r','l','d','!', 0x00};
	Api._printf(msg);
	return 0;
}
