# Introduction #
  * 마인드맵에는 우리가 직관적으로 전개해 나가는 생각과 지식이 녹아들어 있다. 이러한 지식을 체계적으로 정리, 분류하고 검색 가능하게 하면 어떨까? 보다 효율적으로 지식을 저장하고 활용할 수 있지 않을까? 이 프로젝트는 이러한 발상에서 출발한다.
  * [마인드맵 개요](mindmap.md)

# System 구조 #
  * 마인드맵 기반의 지식DB 및 검색시스템은 **마인드맵을 그리고, 이를 DB에 인덱싱하여 저장하고, 검색기능을 제공** 한다.
  * 이를 정리해 보면 크게 세 가지의 Sub-system으로 나눌 수 있다.
  * **WoC** 에서는 세 가지 Sub-system 중 두 번째의 지식 DB 시스템 구축을 목표로 한다.
  * 나머지 Sub-system은 오픈소스 프로젝트화 하여 진행한다.

1. [마인드맵 드로잉 시스템](subsystem1.md) (마인드맵을 그려서 적절한 형식의 데이터포맷으로 저장해주는 시스템) - _추후진행_

2. **[지식 DB 시스템](subsystem2.md) (데이터포맷을 지식검색이 가능한 형식의 데이터로 구조화하는 DB시스템) - WoC 완료**

3. [지식 검색 시스템](subsystem3.md) (검색어를 입력받아 지식DB에서 원하는 검색결과를 얻는 시스템) - _추후진행_

  * Use Case Diagram은 전체 구조를 상위수준에서 개념적으로 나타낸다.
![![](http://mindmap-search.googlecode.com/files/UCD_v1.png)](http://mindmap-search.googlecode.com/files/UCD_v1.png)


# 프로젝트 일정 #
  * [schedule](schedule.md) 페이지를 통해 프로젝트 일정관리를 한다.
  * [첫번째 Iteration 요약](Iteration1.md)
  * [두번째 Iteration 요약](Iteration2.md)

# 관련 자료 #
  * [Links](Links.md) 페이지를 통해 관련 자료 및 링크를 축적한다.

# WoC 멘토가 제시하는 프로젝트 대원칙 #
  * 즐기자.
  * 확장가능하게 하자.
  * 완벽보다는 완성하자.