# 마인드맵 드로잉 시스템 #

마인드맵을 그려서 적절한 형식의 데이터포맷으로 저장해주는 시스템

## 세부 Task ##
  * [지식 DB 시스템](subsystem2.md) 작업 이후에 진행하기로 한다.
  * 현재로서는 기존 드로잉 툴인 [Freemind](http://freemind.sourceforge.net/wiki/index.php/Main_Page) 의 파일 형식을 출력으로 사용한다.

## Freemind 파일 형식 분석 ##
  * 기본적으로 Freemind는 마인드맵을 XML 형태로 저장한다.
  * 

&lt;map&gt;

 태그: 최상위 태그로, 버전정보가 표시된다. 버전의 의미는?
  * 

&lt;node&gt;

 태그: 마인드맵 상의 각 태그를 의미한다. parents 태그 내에 child 노드의 태그가 들어가서 nested 형태를 띈다.

### 

&lt;node&gt;

 태그 속성일람 ###
  * CREATED = 생성 시간의 timestamp로 추정
  * ID = 노드별 고유의 ID
  * MODIFIED = 최종 수정 시간의 timestamp로 추정
  * TEXT = 노드의 텍스트
  * POSITION = 가운데 점으로부터의 상대적 위치 (right, left)
  * HGAP = 가운데 점으로부터 가로 위치 차이 정도
  * VSHIFT = 가운데 점으로부터의 상대적 세로 위치 (+면 화면 아래방향, -면 위쪽방향)
  * COLOR = 노드 색깔
  * FOLDED = 현재 화면에 보이는지의 여부 (true, false)

  * 예제 파일
![http://mindmap-search.googlecode.com/files/mm_sample2.png](http://mindmap-search.googlecode.com/files/mm_sample2.png)
```
<map version="0.8.0">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node COLOR="#0066cc" CREATED="1200904774500" ID="Freemind_Link_976202279" MODIFIED="1200916724062" TEXT="&#xc624;&#xb298; &#xbb50; &#xba39;&#xc9c0;?">
<node CREATED="1200904798703" HGAP="45" ID="_" MODIFIED="1200904834640" POSITION="right" TEXT="&#xd55c;&#xc2dd;" VSHIFT="-47"/>
<node CREATED="1200904809187" HGAP="72" ID="Freemind_Link_805573568" MODIFIED="1200904839343" POSITION="left" TEXT="&#xc911;&#xc2dd;" VSHIFT="22"/>
<node COLOR="#ff0099" CREATED="1200904816671" ID="Freemind_Link_1859401452" MODIFIED="1200916701546" POSITION="right" TEXT="&#xc591;&#xc2dd;" VSHIFT="90">
<node CREATED="1200916735296" ID="Freemind_Link_326267406" MODIFIED="1200916740296" TEXT="&#xb3c8;&#xae4c;&#xc2a4;"/>
<node CREATED="1200916744343" ID="Freemind_Link_1496073153" MODIFIED="1200916748265" TEXT="&#xc2a4;&#xd30c;&#xac8c;&#xd2f0;"/>
</node>
</node>
</map>

```