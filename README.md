ROSque project
==============
#
## 프로젝트 개발 동기
* 사람이 들어가기 힘든 공간을 드론으로 3D맵을 만들며 확인하여, 드론으로 장애물을 회피하며 구조물품을 배달하고 특정 피사체를 추적할 수 있는 시스템 구축해 향후 재난상황에 활용 기대

## [SLAM](https://github.com/ldj5123/ROSque/tree/SLAM "Navigation")
    Raspberri pi4 및 Realsense d435, Bebop 2 drone을 이용한 map 생성
## [Navigation](https://github.com/ldj5123/ROSque/tree/Navigation "Navigation")
    위에서 생성한 map을 기반으로 지정한 위치로 Bebop 2 drone을 이동
## [Active Tracking](https://github.com/ldj5123/ROSque/tree/Active_tracking "Navigation")
    Bebop 2 drone 및 OpenCV dnn_detect를 이용해 특정 물체를 추적

* 동영상 링크↓

[![영상](http://img.youtube.com/vi/cQlJKgrlJ7I/0.jpg)](https://www.youtube.com/watch?v=cQlJKgrlJ7I?t=0s)


프로젝트 기간 : 2020.9.9 ~ 2020.10.13
