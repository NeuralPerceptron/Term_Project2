#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// Inventory,Seller,Buyer vector에 들어갈 구조체
struct Product {
    string name;
    int stockNum;
    int price;
    string date;

    //Product안에 정보 넣고 그 후에 이 내용을 vector에 정보 넣을것이다.(생성자역할)
    Product(string& n, int productNum, int p, string d) : name(n), stockNum(productNum), price(p), date(d) {}
};

//정렬 함수들 : Inventory,conve
bool cmpAsdStr(Product a, Product b); //name 오름차순
bool cmpDsdStr(Product a, Product b); //name 내림차순
bool cmpAsdNum(Product a, Product b);//개수 같으면 이름 기준 오름차순, 개수 오름차순
bool cmpDsdNum(Product a, Product b);//개수 같으면 이름 기준 내차순, 개수 내림차순
bool cmpAsdPrice(Product a, Product b);//가격 같으면 이름 기준 오름차순, 가격 오름차순
bool cmpDsdPrice(Product a, Product b);//가격 같으면 이름 기준 내림차순, 가격 내림차순
bool cmpAsdDate(Product a, Product b);//날짜 같으면 이름 기준 오름차순, 날짜 오름차순
bool cmpDsdDate(Product a, Product b);//날짜 같으면 이름 기준 내림차순, 날짜 내림차순


//재고 및 매출액 현황
class Inventory {
protected:
    int revenue; //매출액
    vector<Product> product;  //재고 정보
public:

    Inventory(int revenue = 0) {
        this->revenue = revenue;
    }

    //재고 변동, v가 편의점, product가 재고
    void update(vector<Product>& v, int index) {
        for (int x = 0; x < product.size(); x++) {
            if (v[index].name == product[x].name) {
                product[x].stockNum -= v[index].stockNum;
                break;
            }
        }
    }
    //수익은 판매자가 아닌 재고에서 관리하게끔 설정해놨다, 구매자가 물품을 구매하면 +값으로 받는다. 매출액 업데이트.
    void update(int revenue) {
        this->revenue += revenue;
    }
    //반품한것은 수익에서 음수값을 받도록 한다. 매출액 데이트.
    void minusUpdate(int revenue) {
        this->revenue -= revenue;
    }

    //재고에 들어갈 물품들을 등록하는 과정
    void InputInventory() {
        while (true) {
            string productName = "";
            int productNum = 0;
            int price = 0;
            string date = "";

            cout << "물품 이름을 입력해주세요(exit를 누르면 나갑니다!!): ";
            getline(cin, productName);
            if (productName == "exit") break;

            cout << "해당 물품 개수를 입력해주세요 : ";
            //물품은 항상 양수, 음수는 예외처리
            while (true) {
                cin >> productNum;
                if (productNum > 0)
                    break;
                else
                    cout << "재고는 1개 이상이어야 합니다. 다시 입력해주세요 : ";
            }

            cout << "해당 물품 가격을 입력해주세요 : ";
            //가격은 항상 양수, 음수는 예외처리
            while (true) {
                cin >> price;
                cin.ignore();
                if (price > 0) {
                    //재고를 등록할때는 업체에서 사오는것이므로 수익에 - 값이다.(편의점에 등록할때 해당 물품의 +20% 가격으로 등록된다.)
                    revenue -= (price * productNum);
                    break;
                }
                else
                    cout << "가격은 양수입니다. 다시 입력해주세요 : ";
            }
            //날짜 입력받기
            cout << "해당 물품 입고 날짜를 입력해주세요(nnnn년nn월nn일) : ";
            getline(cin, date);

            //입력한 값들을 Product벡터에 입력정보 넣기
            product.push_back(Product(productName, productNum, price, date));
        }
    }

    //정렬함수들 : sort함수를 이용해서 정렬한다.
    void asdStr() {
        sort(product.begin(), product.end(), cmpAsdStr);
    }
    void dsdStr() {
        sort(product.begin(), product.end(), cmpDsdStr);
    }
    void asdNum() {
        sort(product.begin(), product.end(), cmpAsdNum);
    }
    void dsdNum() {
        sort(product.begin(), product.end(), cmpDsdNum);
    }
    void asdPrice() {
        sort(product.begin(), product.end(), cmpAsdPrice);
    }
    void dsdPrice() {
        sort(product.begin(), product.end(), cmpDsdPrice);
    }
    void asdDate() {
        sort(product.begin(), product.end(), cmpAsdDate);
    }
    void dsdDate() {
        sort(product.begin(), product.end(), cmpDsdDate);
    }

    //등록 재고 물품들 보기
    void inventoryInfo() {
        cout << "********************************************************************************************************" << endl;
        cout << left << setw(15) << "물품 이름" << setw(15) << "재고 개수" << setw(15) << "각 가격" << setw(15) << "입고 날짜" << endl;
        cout << "********************************************************************************************************" << endl;
        for (int x = 0; x < product.size(); x++) {
            cout << left << setw(15) << product[x].name << setw(15) << product[x].stockNum << setw(15) << product[x].price << setw(15) << product[x].date << endl;
        }
        cout << endl << endl;
    }

    //추가적인 재고를 입력받을시에 입력받기
    void addProduct() {
        InputInventory();
    }

    //매출액 보기
    int getRevenue() {
        return revenue;
    }
    //product 반환
    vector<Product>& getProductVector() {
        return product;
    }
};

//판매자가 편의점을 같이 관리하니, 판매자로 클래스를 구성했다.(제품 클래스는 따로 설정하지않았습니다.)
class Seller : public Inventory {

protected:
    vector<Product> convenience;
public:

    //반품한 내용을 담기
    void updateConvenience(vector<Product> updateConvenience) {
        convenience = updateConvenience;
    }

    //편의점 판매정보 등록하기
    vector<Product> registerConvenience(vector<Product>& inventoryProduct) {
        string convenienceRegisterName = ""; //편의점 제품에 등록할 이름 변수
        int convenienceRegisterNum = 0; //편의점 제품에 등록할 개수 변수
        bool foundProduct = false; //상품을 찾기 위한 flag 같은 역할
        int index = 0; //상품을 찾으면 해당하는 상품의 가격과 날짜를 가지고 오기위한 변수
        int price = 0;
        string date = "";

        cout << "제품정보를 입력하여주세요 : ";
        while (true) {
            getline(cin, convenienceRegisterName);
            //입력한 물품이 재고안에 있을시에 편의점 물품에 등록할수있게끔 설정해놨다.
            for (int x = 0; x < inventoryProduct.size(); x++) {
                if (convenienceRegisterName == inventoryProduct[x].name) {
                    foundProduct = true;
                    index = x;
                    break;
                }
            }
            //입력한 물품이 있을시 수량을 입력한다.
            if (foundProduct) {
                cout << "해당 제품의 수량을 입력해주세요 : ";

                //해당 제품 개수 입력받기 + 예외처리(재고에 있는 상품 개수보다 크면 안된다.)
                while (true) {
                    cin >> convenienceRegisterNum;
                    cin.ignore();

                    if (convenienceRegisterNum > inventoryProduct[index].stockNum && convenienceRegisterNum) {
                        cout << "해당 제품의 개수를 다시 입력해주세요 : ";
                    }
                    else {
                        break;
                    }
                }

                //재고에 있는 가격에 20% 얹어서 편의점에 등록한다. 입고날짜는 그대로 가져왔다.
                price = inventoryProduct[index].price + (inventoryProduct[index].price * 0.2);
                date = inventoryProduct[index].date;

                //convenience에 편의점 판매제품의 정보를 넣어준다.
                convenience.push_back(Product(convenienceRegisterName, convenienceRegisterNum, price, date));

                break;
            }
            //입력한 물품이 없을시에 다시 입력하기.
            if (!foundProduct) {
                cout << "해당하는 제품이 없습니다. 다시입력해주세요 : ";
            }
        }
        //편의점에 등록한 물품들 반환
        return convenience;
    }

    //편의점 정보 내용 보기.
    void registerConvenienceInfo() {
        cout << "********************************************************************************************************" << endl;
        cout << left << setw(15) << "물품 이름" << setw(15) << "재고 개수" << setw(15) << "각 가격" << setw(15) << "입고 날짜" << endl;
        cout << "********************************************************************************************************" << endl;
        for (int x = 0; x < convenience.size(); x++) {
            cout << left << setw(15) << convenience[x].name << setw(15) << convenience[x].stockNum << setw(15) << convenience[x].price << setw(15) << convenience[x].date << endl;
        }
        cout << endl << endl;
    }

    //정렬함수들(convenience 벡터를 위한 정렬 함수들)
    void asdStr() {
        sort(convenience.begin(), convenience.end(), cmpAsdStr); //문자 오름차순
    }
    void dsdStr() {
        sort(convenience.begin(), convenience.end(), cmpDsdStr);//문자 내림차순
    }
    void asdNum() {
        sort(convenience.begin(), convenience.end(), cmpAsdNum); //개수 오름차순
    }
    void dsdNum() {
        sort(convenience.begin(), convenience.end(), cmpDsdNum); //개수 내림차순
    }
    void asdPrice() {
        sort(convenience.begin(), convenience.end(), cmpAsdPrice); //가격 오름차순
    }
    void dsdPrice() {
        sort(convenience.begin(), convenience.end(), cmpDsdPrice); //가격 내림차순
    }
    void asdDate() {
        sort(convenience.begin(), convenience.end(), cmpAsdDate); //날짜 오름차순
    }
    void dsdDate() {
        sort(convenience.begin(), convenience.end(), cmpDsdDate); //날짜 내림차순
    }
};

//구매자 클래스 : Seller,Inventory객체까지 상속받았다.
class Buyer : public Seller {
protected:
    int haveMoney; //Buyer가 가지고 있는 돈
    vector<Product> buyer; //구매자가 구매한 정보들
public:

    //편의점 물품 장바구니에 담기
    vector<Product>& inputShoppingitems(vector<Product>& convenience) {
        string productName = ""; //편의점에서 살 물품이름
        int productNum = 0; //해당 물품 개수
        bool foundProduct = false; //물품을 찾으면 true, 못찾으면 false
        int index = 0; //물건을 찾을시 편의점에 해당하는 물품의 인덱스를 가져오기
        int price = 0; //산 가격
        string date = "";//입고날짜


        cout << "장바구니에 담을 물건을 입력해주세요 : ";
        while (true) {
            getline(cin, productName);
            //편의점에 물품이 있을시에 구매자가 살수있게끔 설정해놓았다.
            for (int x = 0; x < convenience.size(); x++) {
                if (productName == convenience[x].name) {
                    foundProduct = true;
                    index = x;
                    break;
                }
            }
            //편의점 물품이 있을시.
            if (foundProduct) {
                cout << "물건 개수를 입력해주세요 :";

                //장바구니에 담을 물건이 입력한 개수보다 많으면 안되고 0보다 적어서도 안된다.(예외처리)
                while (true) {
                    cin >> productNum;
                    cin.ignore();
                    //구매자가 사려는 물건의 개수가 해당물품의 등록한 개수보다 많으면 안된다.(예외처리)
                    if (productNum <= convenience[index].stockNum && productNum > 0) break;
                    else if (productNum < 0) {
                        cout << "개수는 양수입니다.";
                    }
                    else {
                        cout << "해당 제품의 개수는 " << convenience[index].stockNum << "개 입니다" << endl;
                        cout << "다시 입력해주세요 :";
                    }
                }

                //편의점의 물품과 입고날짜를 각각 구매자 벡터에 넣기 위해서 초기화
                price = convenience[index].price;
                date = convenience[index].date;

                //구매자 벡터에 정보넣기
                buyer.push_back(Product(productName, productNum, price, date));

                //구매자가 물품을 구매했다면, 편의점에 등록한 물품들도 변동사항이 있게끔 설정해놓았다.
                convenience[index].stockNum = convenience[index].stockNum - productNum;


                break;
            }
            //해당하는 물품이 없을시.
            else if (!foundProduct) {
                cout << "해당하는 상품은 없습니다" << endl;
                break;
            }
        }
        //구매자 벡터 반환
        return buyer;
    }

    //현금 입력해서 물건 사기
    int buyShoppingItems() {
        int money = 0;


        int allProductPrice = 0;
        //구매자가 산 모든 제품들의 가격들 구하기.
        for (int x = 0; x < buyer.size(); x++) {
            allProductPrice += (buyer[x].price * buyer[x].stockNum);
        }

        cout << "총 금액은" << allProductPrice << "입니다가지고 계신 현금을 입력해주세요 : ";
        //가지고 있는 돈은 양수
        while (true) {
            cin >> money;
            cin.ignore();;
            if (money > 0) break;
            else if (money < 0) cout << "다시 입력해주세요 : ";
        }
        //totalPrice에 buyer가 가지고있는 모든 제품의 가격들을 알수있다.
        cout << endl;
        //가지고 있는 돈보다 장바구니에 담긴 물품들의 총 가격이 많으면 안된다.(예외처리)
        if (money > allProductPrice) {
            cout << "계산되었습니다. 거스름돈은" << money - allProductPrice << "입니다" << endl;
            return allProductPrice;
        }
        else {
            cout << "돈이 부족합니다. 구매하신 물품들의 총 금액은 " << allProductPrice << "입니다." << endl;
            cout << "반품하기를 눌러주세요" << endl;
            return 0;
        }
    }


    //장바구니에 있는 물건들 보기
    void shoppingItemsInfo() {
        cout << "********************************************************************************************************" << endl;
        cout << left << setw(15) << "구매 물품" << setw(15) << "개수" << setw(15) << "각 가격" << setw(15) << "입고 날짜" << endl;
        cout << "********************************************************************************************************" << endl;
        for (int x = 0; x < buyer.size(); x++) {
            cout << left << setw(15) << buyer[x].name << setw(15) << buyer[x].stockNum << setw(15) << buyer[x].price << setw(15) << buyer[x].date << endl;
        }
        cout << endl << endl;
    }

    //반품하기
    int refundItmes(vector<Product>& convenience) {
        //반품 물건이 있는지 확인 -> 반품(장바구니에 담기에서 해당 물품이 있을시에만 입력을 받았으니, 편의점에 물건이 있는지는 예외처리를 하지 않아도 된다.

        cout << "반품 할 물건을 입력해주세요 : ";
        string refundProductName = "";
        int refundProductNum = 0;
        bool foundBuyerProduct = false; //환불할 물건이 있는지 확인하기.
        int index = 0;

        while (true) {
            //일단 구매한 물품중에 있는지 확인하기
            getline(cin, refundProductName);
            for (int x = 0; x < buyer.size(); x++) {
                if (refundProductName == buyer[x].name) {
                    foundBuyerProduct = true;
                    index = x;
                    break;
                }
            }
            //반품할 물건을 찾을시
            if (foundBuyerProduct) {
                cout << "반품할 물건의 개수를 입력해주세요 : ";

                //자기가 가지고 있는 물품보다 많거나 음수 (예외처리)
                while (true) {
                    cin >> refundProductNum;
                    cin.ignore();
                    if (refundProductNum <= buyer[index].stockNum && refundProductNum > 0) {

                        haveMoney += (buyer[index].price * refundProductNum); //반품을 했으니 자기가 가지고 있는돈은 환불한 값만큼 증가한다.
                        break;
                    }
                    else if (refundProductNum > convenience[index].stockNum) {
                        cout << "가지고 계신 물품의 개수는 " << buyer[index].stockNum << "입니다" << endl;
                        cout << "다시 입력해주세요 : ";
                    }
                    else if (refundProductNum < 0) {
                        cout << "반품하실 개수는 0보다 큽니다. 다시 입력해주세요 : ";
                    }
                }
                //구매자가 편의점에 반품을 했으니 편의점에 반품한 제품의 개수를 갱신해야한다.
                convenience[index].stockNum += refundProductNum;

                cout << "반품이 완료 되었습니다." << endl;
                
                //반품한 총 가격 구현해서 매출액 변동할것이다.
                int refundPrice = buyer[index].price * refundProductNum;

                buyer[index].stockNum -= refundProductNum;//구매자가 환불을 했으니 구매자가 가지고있는 장바구니는 감소한다.
                return refundPrice;
            }   

            //반품한 물건이 없을시
            if (!foundBuyerProduct) {
                cout << "해당 제품은 구매하신 물품중에 없습니다" << endl;
                break;
            }

        }
    }

};

//전체 메뉴
void totalMenu(); //전체 구성에 대한 메뉴

//재고 및 매출액 함수들
void inventoryMenu(); //재고 및 매출액 전체 메뉴
void inventorySubMenu();//재고 정렬 기준 메뉴
void ascendOrDescend(); //재고 오름차순,내림차순 결정 메뉴
int ascendOrDescendSelect();

//판매자
void sellerMenu();//판매자 전체메뉴

//구매자
void buyerMenu();

int main() {

    //먼저 물품들을 등록부터해야지 진행 가능하다.
    Inventory inventoryItems;
    inventoryItems.InputInventory(); //시작부터 재고안에 물품들을 등록해야지 시작하도록 설정해놨다.

    Seller seller; //판매자 객체 생성
    Buyer buyer; //구매자 객체 생성

    vector<Product> v; //재고변동사항까지 구현하기 위해 필요한 벡터

    int num = 0; //전체 메뉴 선택하기 위한 변수
    while (true) {
        totalMenu(); //전체 메뉴
        cout << "메뉴 번호를 선택해주세요 : ";
        cin >> num;

        cout << endl;

        //재고 및 매출액 현황 내용 구현
        if (num == 1) {
            while (true) {
                inventoryMenu(); //재고 및 매출액안의 세부 구현 메뉴
                int n = 0; //메뉴 번호
                cout << "메뉴 번호를 선택해주세요 : "; //재고 및 매출액안의 세부 구현 메뉴를 선택하기 위함.

                //메뉴가 1~4번까지 있으니 다른것 입력하는것을 방지하기(예외처리)
                while (true) {
                    cin >> n;
                    cin.ignore();
                    if (n > 0 && n < 5) break;
                    else {
                        cout << "다시 입력해주세요 : ";
                    }
                }
                //밑에서 재고 및 매출액 현황 내용안의 세부 구현 메뉴 구성

                //재고 및 매출액 현황 내용
                if (n == 1) {
                    inventoryItems.inventoryInfo(); //등록한 물품들을 보여준다

                    //정렬된 상태로 볼수있게끔 설정해놓기
                    string confirm = "";
                    cout << "간편하게 보기 위한 정렬이 필요하십니까?(yes_or_no), no입력시 전체 메뉴로 돌아갑니다. : ";
                    while (true) {
                        getline(cin, confirm);
                        if (confirm == "yes" || confirm == "no") break;
                        if (confirm != "yes" || confirm != "no") cout << "yes or no 로 대답해주세요 !" << endl;
                    }

                    //만약 yes라면 정렬에 관해서 볼수있게끔한다.
                    if (confirm == "yes") {
                        inventorySubMenu(); //정렬에 관한 세부 메뉴

                        int selectSortNum = 0; //정렬 선택 번호

                        //정렬은 1 ~ 5번까지 메뉴가 있다. 그 이외의것은 예외처리
                        while (true) {
                            cout << "정렬 기준을 선택해주세요!! : ";
                            cin >> selectSortNum;
                            cin.ignore();

                            if (selectSortNum > 0 && selectSortNum <= 5) {
                                break;
                            }
                            else {
                                cout << "1~5번까지의 선택이 있습니다. 다시 선택해주세요 : ";
                            }
                        }
                        //이름
                        if (selectSortNum == 1) {

                            while (true) {
                                int selectSortNum_version1 = ascendOrDescendSelect();

                                //오름차순
                                if (selectSortNum_version1 == 1) {
                                    inventoryItems.asdStr();
                                    inventoryItems.inventoryInfo();
                                }
                                //내림차순
                                else if (selectSortNum_version1 == 2) {
                                    inventoryItems.dsdStr();
                                    inventoryItems.inventoryInfo();
                                }
                                //종료
                                else if (selectSortNum_version1 == 3) {
                                    break;
                                }
                                //예외처리
                                else {
                                    cout << "잘못입력하셨습니다 다시 입력해주세요 !!" << endl;
                                }
                            }
                        }
                        //개수
                        else if (selectSortNum == 2) {
                            while (true) {
                                int selectSortNum_version2 = ascendOrDescendSelect();

                                //오름차순
                                if (selectSortNum_version2 == 1) {
                                    inventoryItems.asdNum();
                                    inventoryItems.inventoryInfo();
                                }
                                //내림차순
                                else if (selectSortNum_version2 == 2) {
                                    inventoryItems.dsdNum();
                                    inventoryItems.inventoryInfo();
                                }
                                //종료
                                else if (selectSortNum_version2 == 3) {
                                    break;
                                }
                                //예외처리
                                else {
                                    cout << "잘못입력하셨습니다 다시 입력해주세요 !!";
                                }
                            }
                        }
                        //가격
                        else if (selectSortNum == 3) {

                            while (true) {
                                int selectSortNum_version3 = ascendOrDescendSelect();

                                //오름차순
                                if (selectSortNum_version3 == 1) {
                                    inventoryItems.asdPrice();
                                    inventoryItems.inventoryInfo();
                                }
                                //내림차순
                                else if (selectSortNum_version3 == 2) {
                                    inventoryItems.dsdPrice();
                                    inventoryItems.inventoryInfo();
                                }
                                //종료
                                else if (selectSortNum_version3 == 3) {
                                    break;
                                }
                                //예외처리
                                else {
                                    cout << "잘못입력하셨습니다 다시 입력해주세요 !!";
                                }
                            }
                        }
                        //날짜
                        else if (selectSortNum == 4) {
                            while (true) {
                                int selectSortNum_version4 = ascendOrDescendSelect();

                                //오름차순
                                if (selectSortNum_version4 == 1) {
                                    inventoryItems.asdDate();
                                    inventoryItems.inventoryInfo();
                                }
                                //내림차순
                                else if (selectSortNum_version4 == 2) {
                                    inventoryItems.dsdDate();
                                    inventoryItems.inventoryInfo();
                                }
                                //종료
                                else if (selectSortNum_version4 == 3) {
                                    break;
                                }
                                //예외처리
                                else {
                                    cout << "잘못입력하셨습니다 다시 입력해주세요 !!";
                                }
                            }
                        }
                        //종료
                        else if (selectSortNum == 5) {
                            cout << "종료하겠습니다." << endl;
                        }
                    }
                    //정렬을 보지 않는다면 재고 및 매출액의 세부메뉴로 돌아간다.
                    else if (confirm == "no") break;
                }

                //재고 매출
                else if (n == 2) {
                    int revenue = inventoryItems.getRevenue();
                    cout << "재고 매출 : " << revenue << endl;
                }
                //추가적인 재고 입력
                else if (n == 3) {
                    inventoryItems.addProduct();
                }
                //재고 및 매출액 현황 종료하기
                else if (n == 4) {
                    cout << "재고 및 매출액 현황 내용을 종료합니다" << endl;
                    break;
                }
                //종료
                else {
                    cout << "잘못된 입력입니다 !!" << endl;
                }
            }
        }

        //판매자 + 편의점 현황 내용 구현하기
        else if (num == 2) {
            bool flag = false; //종료할때 사용하기 위한 flag 변수 선언
            while (true) {
                sellerMenu(); //판매자에 관한 전체메뉴
                int n = 0;
                cout << "메뉴를 선택하여주세요 : ";

                //메뉴 잘못선택하는것 예외처리
                while (true) {
                    cin >> n;
                    cin.ignore();

                    if (n > 0 && n < 4) break;
                    else {
                        cout << "잘못된 입력입니다. 다시입력해주세요 : ";
                    }
                }

                vector<Product> tmp = inventoryItems.getProductVector(); //tmp로 재고 정보를 받았다.
                int index = 0;
                while (true) {
                    //편의점 판매제품 등록하기.
                    if (n == 1) {
                        inventoryItems.inventoryInfo(); //재고 및 매출액안의 재고들을 보기 위해서 선언했다.(편의점 제품들을 등록하기 위한 편의상으로 선언)

                        v = seller.registerConvenience(tmp);//registerConvenience를 통해서 편의점 판매제품도 등록받기

                        //재고에 있는 물품들을 등록하면 재고에 있는 해당 등록 물품의 개수가 편의점 등록물품의 개수만큼 없어지므로 재고 변동사항을 갱신했다.
                        for (int x = 0; x < v.size(); x++) {
                            index++;
                        }
                        index--;
                        inventoryItems.update(v, index);
                        break;
                    }

                    //편의점 등록제품 내용 보기
                    else if (n == 2) {
                        seller.registerConvenienceInfo(); //편의점의 등록 물품들을 보기위함.

                        //정렬하기를 원하는지 안하는지 
                        string confirm = "";
                        cout << "간편하게 보기 위한 정렬이 필요하십니까?(yes_or_no), no입력시 전체 메뉴로 돌아갑니다. : ";
                        while (true) {
                            getline(cin, confirm);
                            if (confirm == "yes" || confirm == "no") break;
                            else if (confirm != "yes" || confirm != "no") cout << "yes or no 로 대답해주세요 !" << endl;
                        }


                        //편의점에 등록한 내용을 정렬한 상태로 보기 위해 구현.
                        if (confirm == "yes") {
                            inventorySubMenu(); //정렬에 관한 메뉴

                            int selectSortNum = 0;

                            //정렬 메뉴는 1~5번까지 있으므로 그 외는 예외처리
                            while (true) {
                                cout << "정렬 기준을 선택해주세요!! : ";
                                cin >> selectSortNum;
                                cin.ignore();

                                if (selectSortNum > 0 && selectSortNum <= 5) {
                                    break;
                                }
                                else {
                                    cout << "1~5번까지의 선택이 있습니다. 다시 선택해주세요 : ";
                                }
                            }

                            //이름
                            if (selectSortNum == 1) {

                                //정렬
                                while (true) {
                                    int selectSortNum_version1 = ascendOrDescendSelect();

                                    //오름차순
                                    if (selectSortNum_version1 == 1) {
                                        seller.asdStr();
                                        seller.registerConvenienceInfo();
                                    }
                                    else if (selectSortNum_version1 == 2) {
                                        seller.dsdStr();
                                        seller.registerConvenienceInfo();
                                    }
                                    else if (selectSortNum_version1 == 3) {
                                        break;
                                    }
                                    else {
                                        cout << "잘못입력하셨습니다 다시 입력해주세요 !!" << endl;
                                    }
                                }
                            }

                            //개수
                            else if (selectSortNum == 2) {
                                while (true) {
                                    int selectSortNum_version2 = ascendOrDescendSelect();

                                    //오름차순
                                    if (selectSortNum_version2 == 1) {
                                        seller.asdNum();
                                        seller.registerConvenienceInfo();
                                    }
                                    //내림차순
                                    else if (selectSortNum_version2 == 2) {
                                        seller.dsdNum();
                                        seller.registerConvenienceInfo();

                                    }
                                    //종료
                                    else if (selectSortNum_version2 == 3) {
                                        break;
                                    }
                                    //예외처리
                                    else {
                                        cout << "잘못입력하셨습니다 다시 입력해주세요 !!";
                                    }
                                }
                            }
                            //가격
                            else if (selectSortNum == 3) {
                                while (true) {
                                    int selectSortNum_version2 = ascendOrDescendSelect();

                                    //오름차순
                                    if (selectSortNum_version2 == 1) {
                                        seller.asdPrice();
                                        seller.registerConvenienceInfo();
                                    }
                                    //내림차순
                                    else if (selectSortNum_version2 == 2) {
                                        seller.dsdPrice();
                                        seller.registerConvenienceInfo();

                                    }
                                    //종료
                                    else if (selectSortNum_version2 == 3) {
                                        break;
                                    }
                                    //예외처리
                                    else {
                                        cout << "잘못입력하셨습니다 다시 입력해주세요 !!";
                                    }
                                }
                            }
                            //날짜
                            else if (selectSortNum == 4) {
                                while (true) {
                                    int selectSortNum_version4 = ascendOrDescendSelect();

                                    //오름차순
                                    if (selectSortNum_version4 == 1) {
                                        inventoryItems.asdDate();
                                        inventoryItems.inventoryInfo();
                                    }
                                    //내림차순
                                    else if (selectSortNum_version4 == 2) {
                                        inventoryItems.dsdDate();
                                        inventoryItems.inventoryInfo();
                                    }
                                    //종료
                                    else if (selectSortNum_version4 == 3) {
                                        break;
                                    }
                                    //예외처리
                                    else {
                                        cout << "잘못입력하셨습니다 다시 입력해주세요 !!";
                                    }
                                }
                            }
                        }
                        else if (confirm == "no") {
                            break;
                        }
                    }
                    //종료해서 flag = true를 초기화해줌으로써 서브 메뉴를 나가도록 구성했다.
                    else if (n == 3) {
                        cout << "종료합니다" << endl;
                        flag = true;
                        break;
                    }
                }
                //종료하기
                if (flag == true) {
                    break;
                }
            }
        }

        //고객 정보 내용
        else if (num == 3) {
            while (true) {
                buyerMenu(); //구매자(고객)의 전체 메뉴

                //전체 메뉴 고르기.
                int selectMenu = 0;
                cout << "메뉴를 선택해주세요 : ";
                //예외처리 1~5까지 번호가 있다. 그 외는 예외처리
                while (true) {
                    cin >> selectMenu;
                    cin.ignore();
                    if (selectMenu > 0 && selectMenu < 7) break;
                    else {
                        cout << "다시 입력해주세요 : ";
                    }
                }

                //장바구니 물건 구매하기
                if (selectMenu == 1) {

                   
                    int updateRevenue = buyer.buyShoppingItems(); //현금을 입력해서 물건을 사기위한 함수
                    inventoryItems.update(updateRevenue); //산 가격만큼 매출액을 + 값으로 더해주기위함

                    //물품을 샀을때 전체 매출이 올라가고 장바구니에 담았을때는 매출이 올라가지않게 구현했다.

                }
                //편의점 물품 장바구니에 담기
                else if (selectMenu == 2) {

                    cout << "################################편의점에 등록한 상품들을 보여드리겠습니다#################################" << endl;

                    seller.registerConvenienceInfo(); //편의점에 등록한 물품들을 일단 보기.
                    buyer.inputShoppingitems(v); //고객이 편의점에 등록한 상품들을 담기.
                    seller.updateConvenience(v); //편의점 물품을 등록하면 편의점 물품 갱신하기(편의점 물품 재고 변동)
                }
                //장바구니에 있는 물품들 보기
                else if (selectMenu == 3) {
                    buyer.shoppingItemsInfo();
                }
                //구매한 물품 반품하기
                else if (selectMenu == 4) {

                    buyer.shoppingItemsInfo();
                    int refundPrice = buyer.refundItmes(v); //반품할것들 입력하기
                    seller.updateConvenience(v);//반품한 내역을 편의점 내용에 반환
                    inventoryItems.minusUpdate(refundPrice); //반품한 내역만큼 전체 매출 감소해야한다.

                }
                //구매한 물품들 보기
                else if (selectMenu == 5) {
                    buyer.shoppingItemsInfo();
                }


                //종료
                else if (selectMenu == 6) {
                    break;
                }
            }
        }
        //종료
        else if (num == 4) {
            cout << "안녕히가세요. 구매해주셔서 감사합니다" << endl;
            break;
        }
        //잘못된 입력(예외처리)
        else {
            cout << "*************Warning***************" << endl;
        }
    }
    return 0;
}

//전체메뉴
void totalMenu() {
    cout << "********************************************" << endl;
    cout << "1. 재고 및 매출액 현황 내용" << endl;
    cout << "2. 편의점 현황 내용" << endl;
    cout << "3. 고객 정보 내용 " << endl;
    cout << "4. 종료" << endl;
    cout << "********************************************" << endl;

}
//재고 및 매출액 메뉴
void inventoryMenu() {
    cout << "********************************************" << endl;
    cout << "1.재고 정보 보기" << endl;
    cout << "2.매출액 보기" << endl;
    cout << "3.추가적인 물품 등록하기" << endl;
    cout << "4.종료" << endl;
    cout << "********************************************" << endl;
}
//정렬 메뉴
void inventorySubMenu() {
    cout << "********************************************" << endl;
    cout << "1.물품 이름 기준 정렬" << endl;
    cout << "2.물품 개수 기준 정렬" << endl;
    cout << "3.물품 가격 기준 정렬" << endl;
    cout << "4.물품 날짜 기준 정렬" << endl;
    cout << "5.종료" << endl;
    cout << "********************************************" << endl;
}
//정렬안의 세부 메뉴1
void ascendOrDescend() {
    cout << "********************************************" << endl;
    cout << "1.오름차순 정렬" << endl;
    cout << "2.내림차순 정렬" << endl;
    cout << "3.종료" << endl;
    cout << "********************************************" << endl;
}
//정렬안의 세부 메뉴2
int ascendOrDescendSelect() {
    ascendOrDescend();
    int n = 0;
    cout << "오름차순, 내림차순,종료 중 결정해주세요 : ";
    cin >> n;
    cin.ignore();

    return n;
}
//판매자 메뉴
void sellerMenu() {
    cout << "********************************************" << endl;
    cout << "1.재고안에서 편의점에 물품 등록하기" << endl;
    cout << "2.편의점 등록 제품 보기" << endl; //오름차순,내림차순 구현
    cout << "3.종료" << endl;
    cout << "********************************************" << endl;
}
//구매자 메뉴
void buyerMenu() {
    cout << "********************************************" << endl;
    cout << "1.장바구니 물건 구매하기" << endl;
    cout << "2.편의점 물품 장바구니에 담기" << endl;
    cout << "3.장바구니에 있는 물품들 보기" << endl;
    cout << "4.구매한 물품 반품하기" << endl;
    cout << "5.구매한 물품들 보기" << endl;
    cout << "6.종료" << endl;
    cout << "********************************************" << endl;
}

//name 오름차순
bool cmpAsdStr(Product a, Product b) {
    return a.name < b.name;
}
//name 내림차순
bool cmpDsdStr(Product a, Product b) {
    return a.name > b.name;
}
//개수 같으면 이름 기준 오름차순, 개수 오름차순
bool cmpAsdNum(Product a, Product b) {
    if (a.stockNum == b.stockNum) {
        return a.name < b.name;
    }
    return a.stockNum < b.stockNum;
}
//개수 같으면 이름 기준 내림차순, 개수 내림차순
bool cmpDsdNum(Product a, Product b) {
    if (a.stockNum == b.stockNum) {
        return a.name > b.name;
    }
    return a.stockNum > b.stockNum;
}
//가격 같으면 이름 기준 오름차순, 가격 오름차순
bool cmpAsdPrice(Product a, Product b) {
    if (a.price == b.price) {
        return a.name < b.name;
    }
    return a.price < b.price;
}
//가격 같으면 이름 기준 내림차순, 가격 내림차순
bool cmpDsdPrice(Product a, Product b) {
    if (a.price == b.price) {
        return a.name > b.name;
    }
    return a.price > b.price;
}
//날짜 같으면 이름 기준 오름차순, 날짜 오름차순
bool cmpAsdDate(Product a, Product b) {
    if (a.date == b.date) {
        return a.name < b.name;
    }
    return a.date < b.date;
}
//날짜 같으면 이름 기준 내림차순, 날짜 내림차순
bool cmpDsdDate(Product a, Product b) {
    if (a.date == b.date) {
        return a.name > b.name;
    }
    return a.name > b.name;
}