# Cafe Order & Inventory Manager

[2023-2] Database Programming

![C](https://img.shields.io/badge/C-A8B9CC?style=flat-square&logo=c&logoColor=white)
![MySQL](https://img.shields.io/badge/MySQL-4479A1?style=flat-square&logo=mysql&logoColor=white)

> A terminal-based cafe order and inventory management system built with C and MySQL C API.

<br>

데이터베이스 프로그래밍 과목의 기말 Term 프로젝트로 진행한 2인 팀 프로젝트입니다.

카페 운영에 필요한 **주문 관리**와 **재고 관리** 기능을 하나의 콘솔 프로그램으로 구현했으며,   
주로 **주문 관리 기능 개발**을 담당했습니다.

---

## Project Overview

이 프로젝트는 C 언어에서 데이터베이스를 직접 연결하고 SQL을 처리하는 흐름을 학습하기 위해 구현한 카페 관리 시스템입니다.

단순한 출력 프로그램이 아니라,

- MySQL C API 기반 DB 연결
- SQL 직접 생성 및 실행
- 주문 / 고객 / 재고 데이터 조회 및 수정
- 포인트 및 재고 수량 반영
- 콘솔 메뉴 기반 기능 분기

까지 포함하여, **DB 연동형 CRUD 프로그램의 전체 흐름**을 구현하는 데 초점을 두었습니다.

---

## Key Features

### Order Management
- 메뉴 조회
- 고객 이름 검색
- 신규 고객 등록
- 주문 입력 및 주문 내역 조회
- 주문 취소
- 고객 포인트 적립 / 차감 처리
- 생일 고객 포인트 지급

### Inventory Management
- 재고 주문 내역 조회
- 현재 재고 현황 조회
- 이름 / 회사 / 카테고리 기준 재고 검색
- 재고 주문 입력
- 재고 주문 취소
- 특정 상품 재고 수량 업데이트

---

## My Role

이 프로젝트는 2인 팀 프로젝트로 진행했습니다.

- **공동 수행**
  - 전체 기능 기획
  - 시스템 흐름 및 테이블 구조 구상

- **주 담당 부분**
  - 주문 관리 기능 중심 구현
  - 고객 조회 및 등록
  - 주문 입력 / 취소
  - 주문 내역 조회
  - 고객 포인트 및 생일 포인트 처리

- **협업 구현**
  - 재고 관리 기능
  - 전체 메뉴 흐름 연결 및 테스트

---

## Tech Stack

- **Language**: C
- **Database**: MySQL
- **Library**: MySQL C API
- **Environment**: Linux Server / Terminal

---

## Database Tables

프로그램은 아래 테이블들을 기준으로 동작합니다.

- `menu` : 메뉴 정보
- `cust` : 고객 정보
- `orders` : 주문 정보
- `odetail` : 주문 상세 및 포인트 관련 데이터
- `inventory` : 재고 정보
- `iorders` : 재고 주문 정보
- `supply` : 공급업체 정보

---

## Program Flow

### Order Management Flow
1. 메뉴 또는 고객 정보 조회
2. 신규 고객 등록 또는 기존 고객 검색
3. 주문 입력
4. 주문 내역 조회 및 주문 취소
5. 포인트 적립 / 차감 반영
6. 생일 고객 포인트 지급

### Inventory Management Flow
1. 재고 주문 내역 / 현재 재고 조회
2. 이름 / 회사 / 카테고리 기준 검색
3. 재고 주문 입력
4. 재고 주문 취소
5. 재고 수량 직접 업데이트

---

## Implementation Highlights

### DB Connection
프로그램 시작 시 DB에 연결한 뒤 사용할 데이터베이스를 선택하고, 이후 모든 기능이 해당 연결을 기반으로 동작하도록 구성했습니다.

### Menu-based System Separation
메인 메뉴에서 주문 관리와 재고 관리를 분리하여 기능 흐름을 명확하게 구성했습니다.

### Order Processing Logic
주문 등록 및 취소 시 고객 포인트가 함께 반영되도록 구현했습니다.

### Inventory Update Logic
재고 주문 입력 및 취소 시 재고 수량이 함께 변경되도록 구현했습니다.

### Birthday Point Logic
생일 고객에게 포인트를 지급하고, 중복 지급 여부를 상태값으로 관리하도록 설계했습니다.

---

## What I Learned

- C 언어에서 DB를 직접 연결하고 CRUD를 처리하는 방법
- SQL 실행 결과를 프로그램 로직과 연결하는 방법
- 주문 / 고객 / 재고 데이터 간 관계를 고려한 기능 설계
- 콘솔 환경에서도 메뉴 기반으로 시스템을 구조화하는 방법
- 팀 프로젝트에서 기능을 분담하여 구현하는 협업 방식

---

## Limitations

- 현재는 단일 C 파일 기반 구조로 작성되어 있습니다.
- DB 연결 정보가 코드 내부에 작성되어 있습니다.
- 입력 검증, 예외 처리, 보안 측면에서 추가 개선 여지가 있습니다.
- SQL 초기화 파일이나 실행 가이드는 저장소에 포함되어 있지 않습니다.

---

## Author

Yeeun Park  

GitHub: [DevLucia-21](https://github.com/DevLucia-21)
