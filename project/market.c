// 21500706 지성민
#include "product.h"
#include "manager.h"
#include <stdio.h>
#include <string.h>

int selectMenu() {
    int menu;
    while(1) {
    	printf("\n*** 과자 품목 관리 ***\n");
    	printf("1. 조회\n");
    	printf("2. 추가\n");
    	printf("3. 수정\n");
    	printf("4. 삭제\n");
    	printf("5. 파일저장\n");
    	printf("6. 이름검색\n");
    	printf("7. 가격검색\n");
    	printf("8. 별점검색\n");
    	printf("0. 종료\n");
    	printf("\n=> 원하는 메뉴는? ");
    	scanf("%d", &menu);
	if(0<=menu && menu<9) return menu;
	else printf("Error: incorrect menu number.\n");
    }
}

int main() {
    Product plist[100];
    int curcount = 0;
    int count = 0, menu;
    count = loadData(plist);
    curcount = count;
    #ifdef DEBUG
	printf("--------DEBUG mode----------\n");
	printf("Debug: %s %s %s %d\n", __DATE__, __TIME__, __FILE__, __LINE__);
    #endif
    while(1) {
        menu = selectMenu();
        if(menu == 0) break;
        if(menu == 1 || menu == 3 || menu == 4) {
            if(count == 0) {
                printf("데이터가 존재하지 않습니다.\n");
                continue;
            }
        }
        // Read
        if(menu == 1) {
            if(count > 0) listProd(plist, curcount);
            else printf("데이터가 없습니다.\n");
        }
        // create
        else if(menu == 2) {
            count += addProd(&plist[curcount++]);
        }
        // update
        else if(menu == 3) {
            int no = selectDataNo(plist, curcount);
            if(no == 0 || no == -1) {
                printf("=> 취소됨!\n");
                continue;
            }
            updateProd(&plist[no-1]);
        }
        // delete
        else if(menu == 4) {
            int no = selectDataNo(plist, curcount);
            if(no == 0 || no == -1) {
                printf("=> 취소됨!\n");
                continue;
            }
            int deleteok;
            printf("정말로 삭제하시겠습니까?(삭제 : 1) ");
            scanf("%d", &deleteok);
            if(deleteok == 1) {
                if(deleteProd(&plist[no-1])) count--;
            }
            else printf("삭제되지 않았습니다.\n");
        }
        // Data save
        else if(menu == 5) {
            if(count == 0)
                printf("=> 데이터 없음!\n");
            else {
                saveData(plist, curcount);
            }
        }
	        // search name
        else if(menu == 6) {
            if(count == 0)
                printf("=> 데이터 없음!\n");
            else {
                searchName(plist, curcount);
            }
        }
        // search price
        else if(menu == 7) {
            if(count == 0)
                printf("=> 데이터 없음!\n");
            else {
                searchPrice(plist, curcount);
            }
        }
        // search star
        else if(menu == 8) {
            if(count == 0)
                printf("=> 데이터 없음!\n");
            else {
                searchStar(plist, curcount);
            }
        }
    }
    printf("종료됨!\n");
    return 0;
}
