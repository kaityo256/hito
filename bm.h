#ifndef bm_h
#define bm_h
//----------------------------------------------------------------------
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
//----------------------------------------------------------------------
class WindowsBitmap{
  private:
  int Width, Height,Line;
  BYTE * ImageBuffer;
  int BufferSize;
  int CX, CY; // Current Point
  BYTE R,G,B;
  public:
    WindowsBitmap(int w, int h);
    void MoveTo(int x, int y){CX=x;CY=y;};
    void LineTo(int x, int y);
    void DrawPoint(int x, int y);
    void SetColor(BYTE red,BYTE green,BYTE blue);
    void FillRect(int x, int y, int w, int h);
    void FillCircle(int x, int y, int r);
    void DrawCircle(int x, int y, int r);
    void SaveToFile(const char *filename);
};
//----------------------------------------------------------------------
#endif
