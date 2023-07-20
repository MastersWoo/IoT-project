# IoT Project (스마트팜 (식집사))

그동안 배웠던 것들을 토대로 웹에서 제어 할 수 있는 스마트팜을 구현하는 프로젝트였습니다.


# 프로젝트 구성도

● Tools: Tech

     □ 프론트엔드

      - JavaScript, React, TypeScript

     □ 백엔드

      - Node.js, Express.js, MongoDB, Docker, AWS EC2

     □ 디바이스
      - C, C+, Mosquitto, AWS EC2

● 발표자료 

[SmartFarm_.pdf](https://github.com/MastersWoo/IoT-project/files/12110231/SmartFarm_.pdf)

 <details>
 <summary>Codding Convention</summary>
 <div markdown="1"> 
      
 - Fix 🛠️ : 버그를 고친 경우
    - Feat ➕ : 새로운 기능을 추가할 경우
- Design 🎨 : CSS 등 사용자 UI 디자인 변경
- Change 💎 : 커다란 API 변경의 경우
- Style 👕 : 코드 포맷 변경, 세미 콜론 누락, 코드 수정이 없는 경우
- Hotfix 🚨 : 급하게 치명적인 버그를 고쳐야하는 경우
- Style 👕 : 코드 포맷 변경, 세미 콜론 누락, 코드 수정이 없는 경우
- Refactor 🚧 : 프로덕션 코드 리팩토링
- Comment ✉️ : 필요한 주석 추가 및 변경
- Docs 📝 : 문서를 수정한 경우
- Test 🔍 : 테스트 추가, 테스트 리팩토링(프로덕션 코드 변경 X)
- Chore 🚀 : 빌드 테스트 업데이트, 패키지 매니저를 설정하는 경우
(프로덕션 코드 변경 X)
- Rename 📁 : 파일 혹은 폴더 명을 옮기는 작업만인 경우
- Remove ❌ : 파일을 삭제하는 작업만 수행한 경우
- Release 👏 : 프로젝트 배포할 경우
  
 </div>
 </details>

  <details>
 <summary>API Design Convention</summary>
 <div markdown="1"> 
      
 - `master` : 배포 가능한 상태의 브랜치
    - 버그가 없는 무결한 상태
- `develop` : 평상시에 개발을 진행하는 브랜치
    - 각자 브랜치에서 작업한 상황을 합쳐야한다고 판단할 때 해당 브랜치로 머지하기
- `release-x.x.x` : 배포 버전 기록용 브랜치
- `hot-fix` : `release-x.x.x` (이미 릴리즈한 버전) 에서 문제가 생길 경우 버그를 고치는 브랜치
- `ai` , `front-end` , `back-end` : 각자 개인 레포에서 진행한 작업 상황반영
  
 </div>
 </details>


  <details>
 <summary>Branch Convention</summary>
 <div markdown="1"> 

    - 네이밍
        - Snake Case
        - No Abbreviation
    - 요청 방식
        - Query String
            - GET, DELETE Method
        - Request Body
            - PUT, POST
    - 응답 방식
        - 응답 코드
            - `200` : 성공
            - `400` : 잘못된 요청
                - `401` : 권한 없음
            - `500` : 서버 에러
    - API Guide
        - Required Parameter 의 경우 (*) 로 표현합니다.
        - 정렬 기준은 `GET` → `POST` → `PUT` → `DELETE` 로 합니다.
        
 </div>
 </details>

# Developers & 담당 업무
| 이름 | 포지션 |
| --- | --- |
| 이가은 | 백앤드 / 팀장 |
| 장원경 | 백앤드 | 
| 정혜령 | 프론트 |
| 최혜진 | 프론트 |
| 장재우 | 디바이스 |
