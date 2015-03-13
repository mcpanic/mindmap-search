# 지식 DB 시스템 #

데이터포맷을 지식검색이 가능한 형식의 데이터로 구조화하는 DB시스템

## 설계 방향 ##
  * 지식을 효율적으로 표현할 수 있는 **구조적** 부분과 **시각화** 부분을 균등하게 고려한다. 마인드맵의 특징은 조각조각의 지식을 표현하는 것이 아니라 지식 간의 관계를 시각적으로 나타낸다는 것이다. 이러한 점에 초점을 두고 DB를 설계할 필요가 있다.
  * 구조화된 형태를 상세하게 define하고, 확장성이 있으면서도 검색이 용이한 포맷으로 만든다.

## System Task ##
  * Mindmap 파일을 읽어들여 필요정보를 추출한 뒤 노드 기본 정보와 검색 인덱싱 처리를 한 노드 텍스트로 나누어 DB에 저장한다.
  * 입력: XML 형태의 Mindmap 저장 파일
  * 출력: 노드 DB 와 텍스트 DB

## Interface 설계 ##
  * [XML파서모듈] - [형태소분석모듈] - [가중치산정모듈] - [색인저장모듈] - [물리적DB모듈]
  * 각 모듈들 사이는 인터페이스로 연결된다.

  1. XML 파일을 parse해 나가면서 node 정보를 추출한다. (Xerces XML Parser 활용)
  1. 추출한 정보 중 노드 텍스트에 대해 Tokenize 하여 쪼갠다. (Whitespace 단위로 나눔)
  1. 노드의 중요도에 따라 가중치를 부여한다. _(현재 미구현)_
  1. 인덱싱을 하여 DB 에 저장할 수 있는 형태로 만든다. (현재는 DB모듈과 통합되어 있음)
  1. 노드와 분석한 텍스트를 각각 DB 에 저장한다. (SQLite3 활용)

## DB 설계 ##
  * 두 가지의 DB 테이블이 존재한다.

  * 일반적인 노드 정보를 담는 Node DB
> | NodeID (text) | TimeCre (text) | TimeMod (text) | ParentNodeID (text) |
|:--------------|:---------------|:---------------|:--------------------|


  * 노드의 텍스트를 형태소 분석하여 인덱싱해 저장하는 Text DB (향후 검색엔진의 빠른 처리를 위해 Inverted Index 형태로 구성했다)
> | Token (text)| NodeID (text) | Weight (integer) | Tag (text) | Position (integer) |
|:------------|:--------------|:-----------------|:-----------|:-------------------|


## 마인드맵 노드 설계 ##
```
	string nodeID;            // 노드의 고유 ID
	string nodeName;          // 노드의 이름 (XML 태그 이름)
	string timeCreated;       // 생성시간
	string timeModified;      // 최종수정시간
	string nodeText;          // 노드 텍스트 (검색의 대상)
	string parentNodeID;      // 부모노드의 고유  ID
	vector<string> nodeToken; // 형태소 분석 이후 쪼개진 텍스트
```

## DB를 통해 검색, 계산 가능한 유의미한 요소들 ##
  * 특정 노드를 root로 하는 sub-tree (생각의 작은 단위별 분석)
  * 자식 노드의 수 (연결성이 높다 - 허브역할을 하는 노드)
  * 자식 노드의 리스트 (연관 키워드 검색에 사용가능)
  * 노드 간 거리 (두 노드간의 관계 - 공통 parent 존재하는지/포함관계인지/얼마나 직접적인 관계가 있는지)
  * 트리의 깊이 (?)
  * 최근에 수정된 순서로 노드 정렬 (최근의 trend 파악 가능)
  * 생성된지 오래된 순서로 노드 정렬 (가장 역사깊은 생각 파악 가능)

## 구현 환경 ##
  * 개발환경: Visual Studio 2005
  * 구현언어: C++
  * XML Parser: Xerces-C++ Version 2.8.0 ([Apache](http://www.apache.org/) 재단의 오픈소스인 [Xerces](http://xerces.apache.org/) 프로젝트의 서브셋)
  * DB: [SQLite Version 3](http://www.sqlite.org/)

## 습득한 지식 ##
  * 추상 Interface 를 통한 확장성 있는 OOAD 노하우
  * 검색엔진 DB 구성과 인덱싱 노하우
  * Extreme Programming 기법 (Iteration 기반)
  * Mindmap 의 저장 구조
  * XML parsing 기술
  * SQLite C++ binding 활용 기술

## TODO ##
  * Inverted Index 한 엔트리에 여러 개의 노드 연결시켜 엔트리 수 줄이기
  * 가중치 부여 부분 구현
  * 검색의 효율화를 위해 B-Tree 형태로 변환하기

## 기타 ##
[노트](subsystem2_1.md) 참고