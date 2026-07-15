# DummyDataGenerator-JeonHyunji-10225419

반도체 시료 생산주문관리 시스템 개인과제 — **[미션1] PoC: Dummy 데이터 생성 Tool**

## 목적
테스트를 위한 Dummy Data를 생성하여 연결된 저장소에 추가하는 도구를 검증하는 PoC.

## 기술 스택
- C++20, Visual Studio (MSBuild, .vcxproj)
- nlohmann/json (NuGet, `nlohmann.json`) — JSON 저장소 연동
- gmock (NuGet, v1.11.0) 기반 단위 테스트

## 구조
```
DummyDataGenerator.sln
DummyDataGeneratorLib/
  model/Item.h
  repository/IItemRepository.h, JsonItemRepository.h/.cpp   # save/findAll만 제공 (신규 삽입 전용)
  generator/DummyItemGenerator.h/.cpp                        # 시드 기반 더미 데이터 생성 로직
DummyDataGeneratorApp/     # 콘솔 실행 파일 (개수 입력 → items.json에 삽입), Lib 참조
DummyDataGeneratorTest/    # gmock 테스트 (Mock Repository로 생성 로직 검증), Lib 참조
```
`DummyItemGenerator`는 `IItemRepository`에만 의존하므로, 테스트에서는 실제 파일 대신 `MockItemRepository`로 대체해 `save()` 호출 횟수와 생성된 이름을 검증한다. 같은 시드로 생성하면 항상 같은 이름 시퀀스가 나오도록 재현 가능하게 만들었다.

## 빌드 방법 (Visual Studio)
1. `DummyDataGenerator.sln`을 Visual Studio로 연다.
2. NuGet이 자동으로 `nlohmann.json`(3.12.0), `gmock`(1.11.0)을 복원한다 (안 되면 솔루션 우클릭 → NuGet 패키지 복원).
3. 구성을 **Debug / x64**로 맞추고 `Ctrl+Shift+B` 빌드.

## 실행 방법
- **생성 도구**: `DummyDataGeneratorApp`을 시작 프로젝트로 설정 후 `Ctrl+F5` → 생성할 개수 입력 → `items.json`에 더미 데이터 삽입
  - `DataMonitor-JeonHyunji-10225419`의 `items.json`을 같은 폴더에 두고 실행하면, 삽입된 데이터를 `DataMonitor`로 조회해 확인할 수 있다.
- **테스트**: `DummyDataGeneratorTest`를 시작 프로젝트로 설정 후 `Ctrl+F5` 실행

## 관련 문서
- 상위 저장소의 `PRD.md`, `PLAN.md` Phase 4 참고
