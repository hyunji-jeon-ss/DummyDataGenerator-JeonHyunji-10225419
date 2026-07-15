# CLAUDE.md — DummyDataGenerator-JeonHyunji-10225419

## 프로젝트 개요
Dummy 데이터 생성 Tool PoC. 테스트용 더미 시료/주문 데이터를 생성하여 `DataPersistence` PoC에서 검증한 저장소에 실제로 삽입한다.

## 기술 스택 / 컨벤션
- C++20, Visual Studio(MSBuild, .vcxproj), gmock(NuGet)
- 코드 컨벤션은 상위 `Semiconductor` 폴더의 `CODE_CONVENTION.md`를 따른다.

## 설계 방향
- 랜덤/시드 기반으로 더미 데이터를 생성
- 생성 후 실제 저장소(Repository)에 삽입까지 수행
- 생성 결과는 `DataMonitor` PoC로 확인 가능해야 함

## 테스트
- 저장소 인터페이스를 gmock으로 목킹하여 생성 로직(개수, 데이터 유효성)을 단위 테스트한다.

## 빌드/실행
Visual Studio에서 솔루션을 열어 빌드/실행한다.
