# Linux_Rogue
- make a rogue game (a root of Diablo)

### ncurses 설치 방법
#### Linux
```
sudo apt install libncurses5-dev
```

#### Mac
```
curl -O ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.2.tar.gz
tar -xzvf ncurses-6.2.tar.gz
cd ncurses-6.2
./configure --prefix=/usr/local \
--without-cxx --without-cxx-binding --without-ada --without-progs --without-curses-h \
--with-shared --without-debug \
--enable-widec --enable-const --enable-ext-colors --enable-sigwinch --enable-wgetch-events \
sudo make install
```

### 실행영상
![영상](https://user-images.githubusercontent.com/50474972/113121643-d0506980-924d-11eb-9d40-d3f6467e63fd.gif)

```
  🤺 : 플레이어
  🏔 : 벽
  🐉 : 몬스터, 몬스터에게 갈 시 죽음
  🌟 : 별, 획득 시 게임 클리어
  🐟 : 음식, 획득 시 체력 10 회복
  🔥 : 불, 닿을 시 체력 10 감소
```

### 실행 방법
```
  1. git clone https://github.com/KimUJin3359/Linux_Rogue.git
  2. cd Linux_Rogue
  3. make // or skip
  4. ./game
  
  조작 방법 : 방향키
```

### 사용 
- ncurses : 새 창 띄우기
- locale : Unicode
- pthread : 몬스터의 움직임

#### 알게된 점
- 같은 유니코드라해도 byte가 다를 수 있음



