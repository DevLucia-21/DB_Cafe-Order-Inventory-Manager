#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mysql.h>
#include <time.h>

MYSQL mysql;

void dbConn();
void printErr();
void sendQuery(char *);
void getResult();
void printFields(MYSQL_RES *);

void printMenu();
void selectMenu();
void printCMenu();
void printOrder();
void searchName(char *name);
void inputCust();
void inputOrder();
void deleteOrder();
void plusCustPoints();
void minusCustPoints(int oid);
void updateCustBirthday();
void iprintMenu();
void iprintOrder();
void iprintInventory();
void iselectMenu();
void isearchMenu();
void isearchName();
void iinputOrder();
void ideleteOrder();
void imanageInventory();
void systemChoice();

int getCurrentYear();
void resetbOX();

int year;

char *result[10];

int main() {
        dbConn();
        sendQuery("use db212026");
        year = getCurrentYear();

        systemChoice();

        mysql_close(&mysql);
        return 0;
}

void systemChoice() {
        while(1) {
                int systemChoice;

                printf("-------------------\n");
                printf(" 1. 주문관리 시스템\n");
                printf(" 2. 재고관리 시스템\n");
                printf(" 0. 종료\n");
                printf("-------------------\n");
                printf("시스템 선택: ");
                scanf("%d", &systemChoice);

                if(systemChoice == 0) {
                        printf("종료\n");
                        exit(0);
                }
                switch (systemChoice) {
                        case 1:
                                selectMenu(); // Order Management System
                                break;
                        case 2:
                                iselectMenu(); // Inventory Management System
                                break;
                        default:
                                printf("잘못된 선택입니다.\n");
                                //break;
                }
        }
}

void dbConn() {
        mysql_init(&mysql);
        if (!mysql_real_connect(&mysql, "localhost", "db212026", "net123", "db212026", 0, NULL, 0))
                printErr(&mysql);
        printf("접속되었습니다!!!\n");
}

void printMenu() {
        printf("----------------------------\n");
        printf(" 1. 메뉴판 확인\n");
        printf(" 2. 고객 검색(이름)\n");
        printf(" 3. 주문 입력\n");
        printf(" 4. 주문 삭제(oid)\n");
        printf(" 5. 주문 내역 확인\n");
        printf(" 6. 신규 고객 입력\n");
        printf(" 7. 고객 생일 포인트 적립\n");
        printf(" 9. 뒤로 가기\n");
        printf(" 0. 종료\n");
        printf("----------------------------\n");
}

void selectMenu() {
        int menu, oid;
        char name[100];
        while (1) {
                printMenu();
                printf("menu : ");
                scanf("%d", &menu);
                if (menu == 0) {
                        printf("종료\n");
                //      break;
                        exit(0);
                }
                switch (menu) {
                        case 1:
                                printCMenu();
                                break;
                        case 2:
                                printf("Input name: ");
                                scanf("%s", name);
                                searchName(name);
                                break;
                        case 3:
                                inputOrder();
                                break;
                        case 4:
                                printf("Input oid: ");
                                scanf("%d", &oid);
                                deleteOrder(oid);
                                break;
                        case 5:
                                printOrder();
                                break;
                        case 6:
                                inputCust();
                                break;
                        case 7:
                                updateCustBirthday();
                                resetbOX();
                                break;
                        case 9:
                                systemChoice();
                                return;
                        default:
                            printf("잘못된 번호입니다!!!\n");
                }
        }
}

void printCMenu() {
        printf("-------------------------------------------------------------\n");
        char q[100] = "select * from menu";
        sendQuery(q);
        getResult();
        printf("-------------------------------------------------------------\n");
}

void printOrder() {
        printf("---------------------------------------------------------------------------------------------------------\n");
        char q[100] = "select * from orders";
        sendQuery(q);
        getResult();
        printf("---------------------------------------------------------------------------------------------------------\n");
}

void searchName(char *name) {
        printf("---------------------------------------------------------------------------------------------------------\n");
        char q[100] = "select * from cust where cname='";
        strcat(q, name);
        strcat(q, "'");
        sendQuery(q);
        getResult();
        printf("---------------------------------------------------------------------------------------------------------\n");
}

void inputCust() {
        printf("---------------------------------------------------------------------\n");
        int cid, point;
        char cname[100], hp[100], birthday[100], sORc[100], bOX[100], temp[100];
        char q[200] = "insert into cust values(";
        char q0[10] = ",";
        char q1[10] = "'";
        char q2[10] = ")";
        printf("Input cust(cid | cname | point | hp | birthdy('-'제외) | sORc | bOX): \n");
        scanf("%d %s %d %s %s %s %s", &cid, cname, &point, hp, birthday, sORc, bOX);
        char formatB[100];
        sprintf(formatB, "%c%c%c%c-%c%c-%c%c", birthday[0], birthday[1], birthday[2], birthday[3], birthday[4],
                        birthday[5], birthday[6], birthday[7]);
        sprintf(temp, "%d", cid);
        strcat(q, temp);
        strcat(q, q0);
        strcat(q, q1);
        strcat(q, cname);
        strcat(q, q1);
        strcat(q, q0);
        sprintf(temp, "%d", point);
        strcat(q, temp);
        strcat(q, q0);
        strcat(q, q1);
        strcat(q, hp);
        strcat(q, q1);
        strcat(q, q0);
        strcat(q, q1);
        strcat(q, formatB);
        strcat(q, q1);
        strcat(q, q0);
        strcat(q, q1);
        strcat(q, sORc);
        strcat(q, q1);
        strcat(q, q0);
        strcat(q, q1);
        strcat(q, bOX);
        strcat(q, q1);
        strcat(q, q2);
        sendQuery(q);
        if (!mysql_affected_rows(&mysql))
                printf("입력이 되지 않았습니다!\n");
        printf("고객이 성공적으로 추가되었습니다!\n");
        printf("----------------------------------\n");
}

void inputOrder() {
        printf("-----------------------------------------------------\n");
        int oid, cid, mid, sid, quantity;
        char options[100], odate[100], temp[100];
        char q[200] = "insert into orders values(";
        char q0[10] = ",";
        char q1[10] = "'";
        char q2[10] = ")";
        printf("Input orders(oid cid mid sid quantity options odate): \n");
        scanf("%d %d %d %d %d %s %s", &oid, &cid, &mid, &sid, &quantity, options, odate);
        sprintf(temp, "%d", oid);
        strcat(q, temp);
        strcat(q, q0);
        sprintf(temp, "%d", cid);
        strcat(q, temp);
        strcat(q, q0);
        sprintf(temp, "%d", mid);
        strcat(q, temp);
        strcat(q, q0);
        sprintf(temp, "%d", sid);
        strcat(q, temp);
        strcat(q, q0);
        sprintf(temp, "%d", quantity);
        strcat(q, temp);
        strcat(q, q0);
        strcat(q, q1);
        strcat(q, options);
        strcat(q, q1);
        strcat(q, q0);
        strcat(q, q1);
        strcat(q, odate);
        strcat(q, q1);
        strcat(q, q2);
        sendQuery(q);

        if (!mysql_affected_rows(&mysql))
                printf("입력이 되지 않았습니다!\n");
        plusCustPoints();
        printf("주문이 성공적으로 추가되었습니다!\n");
        printf("----------------------------------\n");
}

void plusCustPoints() {
        char updatePointQuery[200] = "UPDATE cust c \
                                      JOIN odetail o ON c.cid = o.cid \
                                      SET c.point = c.point + if(c.sORc = 's', o.totalP * 5, o.totalP)";
        sendQuery(updatePointQuery);
}

void deleteOrder(int oid) {
        minusCustPoints(oid);
        char deleteOrderQuery[100];
        sprintf(deleteOrderQuery, "DELETE FROM orders WHERE oid=%d", oid);
        sendQuery(deleteOrderQuery);
        if (!mysql_affected_rows(&mysql))
                printf("삭제가 되지 않았습니다!\n");
        else
                printf("주문이 성공적으로 삭제되었습니다!\n");
}

void minusCustPoints(int oid) {
        char updatePointQuery[200];
        sprintf(updatePointQuery, "UPDATE cust c \
                        JOIN odetail o ON c.cid = o.cid \
                        SET c.point = c.point - if(c.sORc = 's', o.totalP * 5, o.totalP) \
                        WHERE o.oid =%d", oid);
        sendQuery(updatePointQuery);
}

void updateCustBirthday() {
        char checkbOXQuery[200];
        sprintf(checkbOXQuery,
                        "SELECT bOX FROM cust WHERE MONTH(birthday) = MONTH(CURRENT_DATE()) AND DAYOFMONTH(birthday-1) = DAYOFMONTH(CURRENT_DATE())");
        sendQuery(checkbOXQuery);

        MYSQL_RES *res = mysql_store_result(&mysql);
        MYSQL_ROW row = mysql_fetch_row(res);

        if (!row || (strcmp(row[0], "o") != 0 || row[0] == NULL)) {
                char updateBirthdayQuery[200];
                sprintf(updateBirthdayQuery,
                                "UPDATE cust SET point = point + 3000, bOX = 'o' WHERE MONTH(birthday) = MONTH(CURRENT_DATE()) AND DAYOFMONTH(birthday-1) = DAYOFMONTH(CURRENT_DATE())");
                sendQuery(updateBirthdayQuery);

                int affectedRows = mysql_affected_rows(&mysql);
                printf("생일자 수: %d\n", affectedRows);

                if (affectedRows == 0)
                        printf("생일 축하 포인트가 업데이트 되지 않았습니다!\n");
                else {
                        printf("생일 축하 포인트가 성공적으로 추가되었습니다!\n");

                        printf("생일 고객: \n");
                        printf("------------------------------\n");
                        char q[200] = "select cid, cname from cust WHERE MONTH(birthday) = MONTH(CURRENT_DATE()) AND DAYOFMONTH(birthday-1) = DAYOFMONTH(CURRENT_DATE())";
                        sendQuery(q);
                        getResult();
                        printf("------------------------------\n");
                }
        } else {
                printf("이미 축하 포인트가 추가되었습니다!\n");
        }
        mysql_free_result(res);
}

void resetbOX() {
        int currentYear = getCurrentYear();
        if (currentYear != year) {
                char resetbOXQuery[200];
                sprintf(resetbOXQuery, "UPDATE cust set bOX = 'x'");
                sendQuery(resetbOXQuery);
                year = currentYear;
        }
}

int getCurrentYear() {
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        return tm_info->tm_year + 1900;
}

void printFields(MYSQL_RES *res) {
        MYSQL_FIELD *fields;
        int fnum, i;
        fnum = mysql_num_fields(res);
        fields = mysql_fetch_fields(res);
        for (i = 0; i < fnum; i++)
                printf("%13s  ", fields[i].name);
        printf("\n");
}

void getResult() {
        MYSQL_RES *res;
        MYSQL_ROW row;
        int fields, i;
        res = mysql_store_result(&mysql);
        if (res == NULL) {
                printErr(&mysql);
                return;
        }
        printFields(res);
        fields = mysql_num_fields(res);
        while (row = mysql_fetch_row(res)) {
                for (i = 0; i < fields; i++)
                        printf("%15s", row[i]);
                printf("\n");
        }
        mysql_free_result(res);
}

void sendQuery(char *query) {
        if (mysql_real_query(&mysql, query, strlen(query)))
                printErr(&mysql);
}

void printErr() {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        exit(1);
}

void iprintMenu() {
        printf("--------------------------------------------\n");
        printf(" 1. 전체 목록 보기(재고 주문 내역,재고 현황)\n");
        printf(" 2. 재고 검색(이름,회사,카테고리)\n");
        printf(" 3. 재고 주문 입력\n");
        printf(" 4. 재고 주문 취소(ioid)\n");
        printf(" 5. 재고 업데이트(iid) \n");
        printf(" 9. 뒤로 가기\n");
        printf(" 0. 종료\n");
        printf("--------------------------------------------\n");
}

void iselectMenu() {
        int menu, ioid, iid;
        char name[100];

        while(1) {
                iprintMenu();
                printf("menu : ");
                scanf("%d", &menu);
                if(menu == 0) {
                        printf("종료\n");
                        //break;
                        exit(0);
                }

                switch(menu) {
                        case 1:
                                printf("1.재고주문내역, 2.재고현황 선택(1 or 2): ");
                                int subMenu;
                                scanf("%d", &subMenu);
                                if (subMenu == 1) {
                                        iprintOrder();
                                } else if (subMenu == 2) {
                                        iprintInventory();
                                } else {
                                        printf("잘못된 선택입니다.\n");
                                }
                                break;
                        case 2:
                                isearchName();
                                break;
                        case 3:
                                iinputOrder();
                                break;
                        case 4:
                                printf("Input ioid: ");
                                scanf("%d", &ioid);
                                ideleteOrder(ioid);
                                break;
                        case 5:
                                printf("Input iid: ");
                                scanf("%d", &iid);
                                imanageInventory(iid);
                                break;
                        case 9:
                                systemChoice();
                                return;
                        default:
                                printf("잘못된 번호입니다!!!\n");
                }
        }
}

void iprintOrder() {
        printf("----------------------------------------------------------------------------------------------\n");
        char q[100]= "select * from iorders";
        sendQuery(q);
        getResult();
        printf("----------------------------------------------------------------------------------------------\n");
}

void iprintInventory() {
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        char q[100] = "select * from inventory";
        sendQuery(q);
        getResult();
        printf("------------------------------------------------------------------------------------------------------------------------\n");
}

void isearchName() {
        int searchOption;
        char searchKeyword[100];

        while(1) {
                printf("-----------------------\n");
                printf("검색 옵션을 선택하세요:\n");
                printf("1. 이름\n");
                printf("2. 회사\n");
                printf("3. 카테고리\n");
                printf("9. 뒤로 가기\n");
                printf("선택: ");
                scanf("%d", &searchOption);
                printf("-----------------------\n");

                switch (searchOption) {
                        case 1:
                                printf("------------------\n");
                                printf("이름을 입력하세요: ");
                                scanf("%s", searchKeyword);
                                printf("------------------\n");
                                break;
                        case 2:
                                printf("--------------------\n");
                                printf("회사를 입력하세요: ");
                                scanf("%s", searchKeyword);
                                printf("--------------------\n");
                                break;
                        case 3:
                                printf("------------------------------\n");
                                printf("카테고리를 입력하세요 (s/i/d): ");
                                scanf("%s", searchKeyword);
                                printf("------------------------------\n");
                                break;
                        case 9:
                                return;
                        default:
                                printf("잘못된 선택입니다.\n");
                                //return;
                }

        char q[200];

        if (searchOption == 1) {
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                sprintf(q, "SELECT * FROM inventory WHERE iname LIKE '%%%s%%'", searchKeyword);
        } else if (searchOption == 2) {
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                sprintf(q, "SELECT * FROM inventory WHERE suid IN (SELECT suid FROM supply WHERE suname LIKE '%%%s%%')", searchKeyword);
        } else if (searchOption == 3) {
                printf("------------------------------------------------------------------------------------------------------------------------\n");
                sprintf(q, "SELECT * FROM inventory WHERE category = '%s'", searchKeyword);
        }

        sendQuery(q);
        getResult();
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        }
}

void iinputOrder() {
        int iid, suid, amount, sid;
        char iodate[100], iname[100], category[10];
        int ea, quantity, limits, iprice;

        printf("input iorders(iid suid amount sid iodate): ");
        scanf("%d%d%d%d%s", &iid, &suid, &amount, &sid, iodate);

        char q_iorders[200];
        sprintf(q_iorders, "insert into iorders values(NULL,%d,%d,%d,%d,'%s')", iid, suid, amount, sid, iodate);
        sendQuery(q_iorders);

        char q_update_inventory[200];
        sprintf(q_update_inventory, "update inventory set quantity = quantity + %d where iid = %d", amount, iid);
        sendQuery(q_update_inventory);

        if (!mysql_affected_rows(&mysql))
                printf("입력이 되지 않았습니다!");
	else
		printf(“입력되었습니다!\n”);
}

void ideleteOrder(int ioid) {
        char q[100];
        sprintf(q, "SELECT iid, amount FROM iorders WHERE ioid = %d", ioid);
        sendQuery(q);
        MYSQL_RES *res = mysql_store_result(&mysql);
        MYSQL_ROW row = mysql_fetch_row(res);

        if (!row) {
                printf("ioid %d에 해당하는 주문을 찾을 수 없습니다.\n", ioid);
                mysql_free_result(res);
                return;
        }

        int iid = atoi(row[0]);
        int amount = atoi(row[1]);

        mysql_free_result(res);

        sprintf(q, "DELETE FROM iorders WHERE ioid = %d", ioid);
        sendQuery(q);

        if (mysql_affected_rows(&mysql) > 0) {
                printf("ioid %d에 해당하는 주문이 성공적으로 취소되었습니다!\n", ioid);
                sprintf(q, "UPDATE inventory SET quantity = quantity - %d WHERE iid = %d", amount, iid);
                sendQuery(q);
                printf("주문 내역이 성공적으로 복구되었습니다!\n");
        } else {
                printf("ioid %d에 해당하는 주문을 취소하는 데 실패했습니다.\n", ioid);
        }
}

void iprintFields(MYSQL_RES *res) {
        MYSQL_FIELD *fields;
        int fnum, i;

        fnum = mysql_num_fields(res); // 필드의 갯수
        fields = mysql_fetch_fields(res); // 모든 필드의 정보
        for(i=0; i<fnum; i++)
                printf("%7s  ",fields[i].name);
        printf("\n");
}


void imanageInventory(int iid) {
        char q[100];
        sprintf(q, "SELECT quantity, limits, suid FROM inventory WHERE iid = %d", iid);
        sendQuery(q);
        MYSQL_RES *res = mysql_store_result(&mysql);
        MYSQL_ROW row = mysql_fetch_row(res);
        int existingQuantity = atoi(row[0]);
        int limit = atoi(row[1]);
        int suid = atoi(row[2]);  // iid에 대한 suid를 직접 가져옴
        mysql_free_result(res);

        printf("현재 기입되어있는 iid의 재고 수 %d: %d\n", iid, existingQuantity);
        int newQuantity;
        printf("업데이트할 재고 수: ");
        scanf("%d", &newQuantity);
        int orderAmount = (limit * 2) - newQuantity;

        if (newQuantity <= limit) {
                time_t t;
                time(&t);
                char iodate[20];
                strftime(iodate, sizeof(iodate), "%Y-%m-%d %H:%M:%S", localtime(&t));

                sprintf(q, "INSERT INTO iorders (iid, suid, amount, sid, iodate) VALUES (%d, %d, %d, NULL, '%s')", iid, suid, orderAmount, iodate);
                sendQuery(q);
        }

        int invenAmount = newQuantity + orderAmount;
        sprintf(q, "UPDATE inventory SET quantity = %d WHERE iid = %d", invenAmount, iid);
        sendQuery(q);

        printf("재고량이 업데이트 되었습니다!\n");
}

void updateQuantity(int iid, int newQuantity) {
        char q[100];
        sprintf(q, "UPDATE inventory SET quantity=%d WHERE iid=%d", newQuantity, iid);
        sendQuery(q);
}

void iaddOrder(int iid, int quantity, int limit) {
        char q[200];
        sprintf(q, "INSERT INTO iorders (iid, suid, amount, sid, iodate) VALUES (%d, NULL, %d, NULL,now())", iid, quantity);
        sendQuery(q);
        printf("iid %d에 대한 주문이 추가되었습니다. 수량: %d, 제한: %d\n", iid, quantity, limit);
}

void isendQuery(char *query) {
        if(mysql_real_query(&mysql, query, strlen(query)))
                printErr(mysql);
}

void iprintErr() {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        exit(1);
}
