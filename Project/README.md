# Project 

### 목표는 식당 추천 역할을 해주는 기능 구현

* 안암동 주변의 음식점, 술집, 카페 데이터 수집 - yelp에서 csv 파일 받아서 새 csv 파일 생성 후 txt파일(Restaurant_information.txt)로 바꿈. (조원 3명이서 식당 카테고리마다 하나씩 맡아서 한 듯함.)

## Restaurant_information.txt
음식점이름 | 장소 | 큰 범위 | 작은 범위 | 평균 가격 | 영업 시간 | 메뉴 1 | 메뉴 2 | 메뉴 3 | 메뉴 1 가격 | 메뉴 2 가격 | 메뉴 3 가격 | 휴무일 |


## 기능 설명

### 1. 첫 번째 기능 : 가게 카테고리 별 가격오름차순 출력 - print_by_expected_cost
    1 : 식당
    2 : 술집
    3 : 카페 및 간식
   
![image](https://user-images.githubusercontent.com/75352656/199527844-c49d6173-4d1b-4187-8d10-3f4ee561ac33.png)


### 2. 두 번째 기능 : 검색 - search
    2-1 : 가게 카테고리 검색
        1 : 식당
        2 : 술집
        3 : 카페 및 간식
    2-2 : 세부 검색
        1 : 위치
        2 : 큰 범주
        3 : 작은 범주
    
    2-3 : 최종 검색
        앞서 선택했던 두 가지 단계에 따른 검색 가능한 리스트들로 가게 검색 가능.
        
![image](https://user-images.githubusercontent.com/75352656/199528039-37f36c44-98e1-4b9a-83ee-84f08f7b82af.png)


### 3. 세 번째 기능 : 1개 가게 입력 시 그와 유사한 가게 추천 - recommend_3_stores
    3-1 : 가게 카테고리 검색
        1 : 식당
        2 : 술집
        3 : 카페 및 간식
    3-2 : 제시하는 가게 중 방문했던 가게 검색이 가능
    
![image](https://user-images.githubusercontent.com/75352656/199528224-21816ef0-4ba0-47df-bf74-012688a20eae.png)


### 4. 네 번째 기능 : 가게 50개에 대한 평점을 모두 등록 시 가게 추천(카페에 한정한 기능)
    cafe_simulation.txt 이용
    예시 input = sample input 4번.txt 이용
    cosine similarity 이용 -> 가게 3개 추천
    PCC similarity 이용 -> 가게 3개 추천
    
![image](https://user-images.githubusercontent.com/75352656/199528490-388c7b00-003a-4dec-ba2c-bb675e59ac84.png)
![image](https://user-images.githubusercontent.com/75352656/199528585-41961d2a-b52c-41c5-bd4b-e37bf88b6eba.png)
