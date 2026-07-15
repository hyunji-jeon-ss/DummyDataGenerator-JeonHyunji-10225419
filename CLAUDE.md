# CLAUDE.md — DummyDataGenerator-JeonHyunji-10225419

## 프로젝트 개요
Dummy 데이터 생성 Tool PoC. 테스트용 더미 시료/주문 데이터를 생성하여 `DataPersistence` PoC에서 검증한 저장소에 실제로 삽입한다.

## 기술 스택 / 컨벤션
- C++20, Visual Studio(MSBuild, .vcxproj), gmock(NuGet)
- nlohmann/json (NuGet 패키지 `nlohmann.json`) — JSON 저장소 연동
- 코드 컨벤션은 `CODE_CONVENTION.md`를 따른다.

## 구조
```
DummyDataGeneratorLib/    # model/, repository/(IItemRepository, JsonItemRepository — save/findAll만), generator/(DummyItemGenerator)
DummyDataGeneratorApp/    # 콘솔 실행 파일 (main.cpp), Lib 참조
DummyDataGeneratorTest/   # gmock 단위 테스트 (MockItemRepository로 생성 로직 검증), Lib 참조
```

## 설계 방향
- 시드 기반으로 더미 데이터를 생성 (동일 시드 → 동일 이름 시퀀스, 재현 가능)
- 생성 후 실제 저장소(Repository)에 삽입까지 수행
- 생성 결과는 `DataMonitor` PoC로 확인 가능해야 함

## 테스트
- 저장소 인터페이스를 gmock으로 목킹하여 생성 로직(개수, 데이터 유효성)을 단위 테스트한다.

## 한글 인코딩 (중요)
콘솔에 한글을 출력하므로 반드시 아래 두 가지를 유지한다. 자세한 이유는 상위 `Semiconductor` 폴더의 `CLAUDE.md` 참고.
1. 모든 `.vcxproj`의 각 ClCompile 설정에 `<AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>` 적용
2. 콘솔 진입점(main)에서 `SetConsoleOutputCP(CP_UTF8)` / `SetConsoleCP(CP_UTF8)` 호출

## 커밋 컨벤션
`COMMIT_CONVENTION.md`를 따른다. 커밋 메시지는 `<헤더> 변경 내용` 형식이며, 헤더는 `<FEATURE>`/`<FIX>`/`<DOCS>`/`<STYLE>`/`<REFACTOR>`/`<TEST>`/`<CHORE>` 중 하나만 사용한다.

## 빌드/실행
Visual Studio에서 솔루션을 열어 빌드/실행한다. **빌드가 실패한 상태에서는 절대 커밋하지 않는다** — 반드시 로컬 빌드 성공(및 가능하면 테스트 통과)을 확인한 뒤 커밋한다. 자세한 내용은 상위 `Semiconductor` 폴더의 `CLAUDE.md` 참고.
