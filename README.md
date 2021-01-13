# 人と人が支え合った時のストレス

## 概要

どこかのテレビ番組で「『人』という字は人と人が支え合ってできている」的なことを言ってたらしいので、
実際に支え合ったらどちらにどのくらいのストレス(応力)がかかっているかを計算してみるコード。

## 使い方

    $ make
    $ ./a.out <hito.data

実行するとbitmapを吐きます。
povファイルも吐いているので、もしpovrayを持っていたら、make pngでレンダリングもできます。

    $ make png

## 実行結果

### ファイル

![bmp1](fig/hito_bmp1.png)
![bmp2](fig/hito_bmp2.png)
![bmp3](fig/hito_bmp3.png)
![bmp4](fig/hito_bmp4.png)

![pov1](fig/hito_pov1.png)
![pov2](fig/hito_pov2.png)
![pov3](fig/hito_pov3.png)
![pov4](fig/hito_pov4.png)

### アニメーションGIF

![gif](fig/hito.gif)

## ライセンス

MIT