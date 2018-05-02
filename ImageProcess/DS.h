//---------------------------------------------------------------------------
#ifndef DSH
#define DSH

#include <algorithm>    // swap
#include <stdexcept>    // exceptions
#include <fstream>

//---------------------------------------------------------------------------

template <class T> class ARRAY
{
public:
    ARRAY(unsigned int = 0);

    ~ARRAY();

    inline T& operator[] (unsigned int);

    void Free(void);

    void New(unsigned int);

    void NewAndInit(unsigned int, T);

    void NewWithoutInit(unsigned int);

    T* Ptr(void);

    unsigned int Length(void);

    ARRAY &operator = (const ARRAY&);
    
    ARRAY &operator = (T val);

    void AssignAllValue(T val);
    
    ARRAY &operator += (const int);

    ARRAY &operator -= (const int);
    
    void SwapContents(ARRAY& Array);

private:
    unsigned int length;

    T *ArrayData;
};

//-----------------------------------------------------------------

template <class T> ARRAY <T> :: ARRAY(unsigned int l)
{
    ArrayData = NULL;
    length = 0;
    New(l);
}

//-----------------------------------------------------------------

template <class T> ARRAY <T> :: ~ARRAY()
{
    Free();
}

//-----------------------------------------------------------------

template <class T> void ARRAY <T> :: New(unsigned int l)
{
    if (l != length && l > 0)
    {
        Free();
        length = l;
        ArrayData = new T[l] ;
    }

    if (l > 0)
        AssignAllValue(0);
}

//-----------------------------------------------------------------

template <class T> void ARRAY <T> :: NewAndInit(unsigned int l, T val)
{
    if (l != length && l > 0)
    {
        Free();
        length = l;
        ArrayData = new T[l] ;
    }

    if (l > 0)
        AssignAllValue(val);
}

//-----------------------------------------------------------------

template <class T> void ARRAY <T> :: NewWithoutInit(unsigned int l)
{
    if (l != length && l > 0)
    {
        Free();
        length = l;
        ArrayData = new T[l];
    }
}

//-----------------------------------------------------------------

template <class T> inline unsigned int ARRAY <T> :: Length(void)
{
    return length;
}

//-----------------------------------------------------------------

template <class T> inline T& ARRAY <T> :: operator[] (unsigned int i)
{
#ifdef _DEBUG
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    if (i >= length)
        throw std::out_of_range("index out of bounds");
#endif
    return ArrayData[i];
}

//-----------------------------------------------------------------

template <class T> void ARRAY <T> :: Free(void)
{
    if (ArrayData != NULL)
    {
        T* TmpArray = ArrayData;
        length = 0;
        ArrayData = NULL;
        delete [] TmpArray;
    }
}

//-----------------------------------------------------------------

template <class T> T* ARRAY <T> :: Ptr(void)
{
#ifdef _DEBUG
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");
#endif

    return ArrayData;
}

//-----------------------------------------------------------------

template <class T> ARRAY <T>& ARRAY <T> :: operator = (const ARRAY &aArray)
{
    if (this == &aArray)
        return *this;

    if (height != aArray.length)
        Free();

    New(aArray.length);

//    for (int i = 0;i < length;i++)
//        ArrayData[i] = (T)aArray.ArrayData[i];

    memcpy(ArrayData, aArray.ArrayData, sizeof(T)*length);

    return *this;
}

//-----------------------------------------------------------------

template <class T> ARRAY <T>& ARRAY <T> :: operator = (T val)
{
    AssignAllValue(val);
    return *this;
}

//-----------------------------------------------------------------

template <class T> void ARRAY<T> :: AssignAllValue(T val)
{
#ifdef _DEBUG
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");
#endif

    for (unsigned int i=0 ; i<length ; ++i)
        ArrayData[i] = (T)val;
}

//-----------------------------------------------------------------

template <class T> ARRAY<T>& ARRAY<T> :: operator += (const int number)
{
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    for (unsigned int i=0 ; i<length ; ++i)
        ArrayData[i] += (T)number;

    return *this;
}

//-----------------------------------------------------------------

template <class T> ARRAY<T>& ARRAY<T> :: operator -= (const int number)
{
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    for (unsigned int i=0 ; i<length ; ++i)
        ArrayData[i] -= (T)number;

    return *this;
}

//-----------------------------------------------------------------

template <class T> void ARRAY <T> :: SwapContents(ARRAY<T>& Array)
{
    std::swap(Array.ArrayData, ArrayData);
    std::swap(Array.length, length);
}

//-----------------------------------------------------------------

template <class T> class ARRAY2D
{
public:
    ARRAY2D();

    ARRAY2D(unsigned int, unsigned int);

    ~ARRAY2D();

    inline T* operator[] (unsigned int);

    void Free(void);

    void New(unsigned int, unsigned int);

    void NewAndInit(unsigned int, unsigned int, T);

    void NewWithoutInit(unsigned int, unsigned int);

    inline unsigned int Height(void);

    inline unsigned int Width(void);

    T** Ptr(void);

    T*  Get1DPtr(void);

    inline unsigned int Get1DLength(void);

    ARRAY2D &operator = (const ARRAY2D&);

    ARRAY2D &operator = (T);

    void AssignAllValue(T);

    ARRAY2D &operator += (const int);

    ARRAY2D &operator -= (const int);

    void SwapContents(ARRAY2D& Array);

    void SaveDataOnly(std::ofstream&);

    void LoadDataOnly(std::ifstream&);

    void SaveDataByText(std::ofstream&);

    void LoadDataByText(std::ifstream&);

private:
    unsigned int width, height;

    unsigned int totallength;

    T **ArrayData;

    T *TotalArrayData;
};

//-----------------------------------------------------------------

template <class T> void ARRAY2D <T> :: SaveDataOnly(std::ofstream& out)
{
    if (!out.is_open()) throw std::invlid_argument("output stream not ready!");

    // 1D ver.
    out.write(TotalArrayData, sizeof(T)*totallength);

    //for (unsigned int h=0 ; h<height ; ++h)
    //    out.write(ArrayData[h], sizeof(T)*width);
}

//-----------------------------------------------------------------

template <class T> void ARRAY2D <T> :: LoadDataOnly(std::ifstream& in)
{
    if (!in.is_open()) throw std::invalid_argument("input stream not ready!");

    // 1D ver.
    in.read(TotalArrayData, sizeof(T)*totallength);

    //for (unsigned int h=0 ; h<height ; ++h)
    //    in.read(ArrayData[h], sizeof(T)*width);
}

//-----------------------------------------------------------------

template <class T> void ARRAY2D <T> :: SaveDataByText(std::ofstream& out)
{
    if (!out.is_open()) throw std::invalid_argument("output stream not ready!");

    for (unsigned int i=0 ; i<totallength ; ++i)
        out << TotalArrayData[i] << ( ((i+1)%width)?"\t":"\n" );
}

//-----------------------------------------------------------------

template <class T> void ARRAY2D <T> :: LoadDataByText(std::ifstream& in)
{
    if (!in.is_open()) throw std::invalid_argument("input stream not ready!");

    for (unsigned int i=0 ; i<totallength ; ++i)
        in >> TotalArrayData[i];
}

//-----------------------------------------------------------------

template <class T> ARRAY2D <T> :: ARRAY2D()
{
    TotalArrayData = NULL;
    ArrayData = NULL;
    totallength = 0;
    height = 0;
    width = 0;
}

//-----------------------------------------------------------------

template <class T> ARRAY2D <T> :: ~ARRAY2D()
{
    Free();
}

//-----------------------------------------------------------------

template <class T> ARRAY2D <T> :: ARRAY2D(unsigned int h, unsigned int w)
{
    ArrayData = NULL;
    TotalArrayData = NULL;
    totallength = 0;
    height = 0;
    width = 0;
    New(h, w);
}

//-----------------------------------------------------------------

template <class T> ARRAY2D <T>& ARRAY2D <T> :: operator = (const ARRAY2D &aArray)
{
    if (this == &aArray)
        return *this;

    if (height != aArray.height || width != aArray.width)
        Free();

    New(aArray.height, aArray.width);

//    for (unsigned int h = 0;h < height;h++)
//    for (unsigned int w = 0;w < width;w++)
//        ArrayData[h][w] = (T)aArray.ArrayData[h][w];

//    for (unsigned int h=0 ; h<height ; ++h)
//        memcpy(ArrayData[h], aArray.ArrayData[h], sizeof(T)*width);

    // 1D ver.
    memcpy(TotalArrayData, aArray.TotalArrayData, sizeof(T)*totallength);

    return *this;
}

//-----------------------------------------------------------------

template <class T> ARRAY2D <T>& ARRAY2D <T> :: operator = (T val)
{
    AssignAllValue(val);
    return *this;
}

//-----------------------------------------------------------------

template <class T> void ARRAY2D <T> :: AssignAllValue(T val)
{
#ifdef _DEBUG
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");
#endif

    //for (unsigned int i = 0;i < height;i++)
    //for (unsigned int j = 0;j < width ;j++)
    //    ArrayData[i][j] = (T)val;

    // 1D ver.
    T* apData  = TotalArrayData;
    for (unsigned int i=0 ; i<totallength ; ++i)
        *apData++ = (T)val;
}

//-----------------------------------------------------------------

template <class T> ARRAY2D <T>& ARRAY2D <T> :: operator += (const int number)
{
#ifdef _DEBUG
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");
#endif

    //for (unsigned int i = 0;i < height;i++)
    //for (unsigned int j = 0;j < width ;j++)
    //    ArrayData[i][j] += (T)number;

    // 1D ver.
    T* apData  = TotalArrayData;
    for (unsigned int i=0 ; i<totallength ; ++i)
        *apData++ += (T)number;

    return *this;
}

//-----------------------------------------------------------------

template <class T> ARRAY2D <T>& ARRAY2D <T> :: operator -= (const int number)
{
#ifdef _DEBUG
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");
#endif

    //for (unsigned int i = 0;i < height;i++)
    //for (unsigned int j = 0;j < width ;j++)
    //    ArrayData[i][j] -= (T)number;

    // 1D ver.
    T* apData  = TotalArrayData;
    for (unsigned int i=0 ; i<totallength ; ++i)
        *apData++ -= (T)number;

    return *this;
}

//-----------------------------------------------------------------

template <class T> void ARRAY2D <T> :: New(unsigned int h, unsigned int w)
{
    if ((h != height || w != width) && (h > 0 && w > 0))
    {
        Free();

        height = h;
        width = w;

        // ArrayData = new T*[h];

        //for (unsigned int i = 0 ; i < h ; ++i)
        //    ArrayData[i] = new T[w];

        // 1D ver.
        totallength = h*w;

        if (totallength < h || totallength < w)
            throw std::overflow_error("the size of array is too large to overlimit.");

        T** aapData = new T*[h];
        T* apData = new T[totallength];

        for (unsigned int i=0 ; i<h ; ++i, apData+=width)
            *aapData++ = apData;

        ArrayData = aapData-h;
        TotalArrayData = apData-totallength;
    }

    AssignAllValue(0);
}

//-----------------------------------------------------------------

template <class T> void ARRAY2D <T> :: NewAndInit(unsigned int h, unsigned int w, T val)
{
    if ((h != height || w != width) && (h > 0 && w > 0))
    {
        Free();

        height = h;
        width = w;

        //ArrayData = new T *[h];

        //for (unsigned int i = 0 ; i < h ; ++i)
        //    ArrayData[i] = new T[w];

        // 1D ver.
        totallength = h*w;

        if (totallength < h || totallength < w)
            throw std::overflow_error("the size of array is too large to overlimit.");

        T** aapData = new T*[h];
        T* apData = new T[totallength];

        for (unsigned int i = 0 ; i < h ; ++i, apData+=width)
            *aapData++ = apData;

        ArrayData = aapData-h;
        TotalArrayData = apData-totallength;
    }

    AssignAllValue(val);
}

//-----------------------------------------------------------------

template <class T> void ARRAY2D <T> :: NewWithoutInit(unsigned int h, unsigned int w)
{
    if ((h != height || w != width) && (h > 0 && w > 0))
    {
        Free();

        height = h;
        width = w;

        //ArrayData = new T *[h];

        //for (unsigned int i = 0 ; i < h ; ++i)
        //    ArrayData[i] = new T[w];

        // 1D ver.
        totallength = h*w;

        if (totallength < h || totallength < w)
            throw std::overflow_error("the size of array is too large to overlimit.");

        T** aapData = new T*[h];
        T* apData = new T[totallength];

        for (unsigned int i = 0 ; i < h ; ++i, apData+=width)
            *aapData++ = apData;

        ArrayData = aapData-h;
        TotalArrayData = apData-totallength;
    }
}

//-----------------------------------------------------------------

template <class T> inline unsigned int ARRAY2D<T> :: Height(void)
{
    return height;
}

//-----------------------------------------------------------------

template <class T> inline unsigned int ARRAY2D<T> :: Width(void)
{
    return width;
}

//-----------------------------------------------------------------

template <class T> inline T* ARRAY2D <T> :: operator[] (unsigned int i)
{
#ifdef _DEBUG
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    if (i >= height)
        throw std::out_of_range("index out of bounds");
#endif
    return ArrayData[i];
}

//-----------------------------------------------------------------

template <class T> void ARRAY2D <T> :: Free(void)
{
    if (ArrayData != NULL)
    {
        T** aapTmp = ArrayData;
        T*  apTmp = TotalArrayData;

        //unsigned int uiHeight = height;

        height = width = totallength = 0;
        ArrayData = NULL;
        TotalArrayData = NULL;

        //for (unsigned int i=0 ; i<uiHeight ; ++i)
        //    if (aapTmp[i] != NULL)
        //        delete[] aapTmp[i];

        delete[] aapTmp;
        delete[] apTmp;
    }
}

//-----------------------------------------------------------------

template <class T> T** ARRAY2D <T> :: Ptr(void)
{
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    return ArrayData;
}

//-----------------------------------------------------------------

template <class T> void ARRAY2D <T> :: SwapContents(ARRAY2D<T>& Array)
{
    std::swap(Array.ArrayData, ArrayData);
    std::swap(Array.height, height);
    std::swap(Array.width, width);
    std::swap(Array.TotalArrayData, TotalArrayData);
    std::swap(Array.totallength, totallength);
}

//-----------------------------------------------------------------

template <class T> T* ARRAY2D <T> :: Get1DPtr(void)
{
    if (NULL == TotalArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    return TotalArrayData;
}

//-----------------------------------------------------------------

template <class T> unsigned int ARRAY2D <T> :: Get1DLength(void)
{
    if (NULL == TotalArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    return totallength;
}

//-----------------------------------------------------------------

template <class T> class ARRAY3D
{

public:
    ARRAY3D();

    ARRAY3D(unsigned int, unsigned int, unsigned int);

    ~ARRAY3D();

    inline T** operator[] (unsigned int i);

    void Free(void);

    void New(unsigned int = 0, unsigned int = 0, unsigned int = 0);

    void NewAndInit(unsigned int, unsigned int, unsigned int, T);

    void NewWithoutInit(unsigned int, unsigned int, unsigned int);

    inline unsigned int Depth(void);

    inline unsigned int Height(void);

    inline unsigned int Width(void);

    T*** Ptr(void);

    ARRAY3D &operator = (const ARRAY3D &aArray);

    ARRAY3D &operator = (T val);
    
    void AssignAllValue(T val);
    
    ARRAY3D &operator += (const int);
    
    ARRAY3D &operator -= (const int);
    
    void SwapContents(ARRAY3D<T>& Array);

private:
    unsigned int width, height, depth;

    T ***ArrayData;
};

//-----------------------------------------------------------------

template <class T> ARRAY3D <T> :: ARRAY3D()
{
    ArrayData = NULL;
    depth  = 0;
    height = 0;
    width  = 0;
}

//-----------------------------------------------------------------

template <class T> ARRAY3D <T> :: ARRAY3D(unsigned int d, unsigned int h, unsigned int w)
{
    ArrayData = NULL;
    depth  = 0;
    height = 0;
    width  = 0;
    New(d, h, w);
}

//-----------------------------------------------------------------

template <class T> ARRAY3D <T> :: ~ARRAY3D()
{
    Free();
}

//-----------------------------------------------------------------

template <class T> void ARRAY3D <T> :: New(unsigned int d, unsigned int h, unsigned int w)
{
    if ((d != depth || h != height || w != width) && (d > 0 && h > 0 && w > 0))
    {
        Free();
        height = h;
        width  = w;
        depth  = d;
        ArrayData = new T **[d];
        for (unsigned int i = 0 ; i < d ; ++i)
        {
            ArrayData[i] = new T *[h];

            for (unsigned int j = 0 ; j < h ; ++j)
                ArrayData[i][j] = new T[w];
        }
    }

    AssignAllValue(0);
}

//-----------------------------------------------------------------

template <class T> void ARRAY3D <T> :: NewAndInit(unsigned int d, unsigned int h, unsigned int w, T val)
{
    if ((d != depth || h != height || w != width) && (d > 0 && h > 0 && w > 0))
    {
        Free();
        height = h;
        width  = w;
        depth  = d;
        ArrayData = new T **[d];
        for (unsigned int i = 0 ; i < d ; ++i)
        {
            ArrayData[i] = new T *[h];

            for (unsigned int j = 0 ; j < h ; ++j)
                ArrayData[i][j] = new T[w];
        }
    }

    AssignAllValue(val);
}

//-----------------------------------------------------------------

template <class T> void ARRAY3D <T> :: NewWithoutInit(unsigned int d, unsigned int h, unsigned int w)
{
    if ((d != depth || h != height || w != width) && (d > 0 && h > 0 && w > 0))
    {
        Free();
        height = h;
        width  = w;
        depth  = d;
        ArrayData = new T **[d];
        for (unsigned int i = 0 ; i < d ; ++i)
        {
            ArrayData[i] = new T *[h];

            for (unsigned int j = 0 ; j < h ; ++j)
                ArrayData[i][j] = new T[w];
        }
    }
}

//-----------------------------------------------------------------

template <class T> inline unsigned int ARRAY3D <T> :: Depth(void)
{
    return depth;
}

//-----------------------------------------------------------------

template <class T> inline unsigned int ARRAY3D <T> :: Height(void)
{
    return height;
}

//-----------------------------------------------------------------

template <class T> inline unsigned int ARRAY3D <T> :: Width(void)
{
    return width;
}

//-----------------------------------------------------------------

template <class T> inline T** ARRAY3D <T> :: operator[] (unsigned int  i)
{
#ifdef _DEBUG
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    if (i >= depth)
        throw std::out_of_range("index out of bounds");
#endif

    return ArrayData[i];
}

//-----------------------------------------------------------------

template <class T> void ARRAY3D <T> :: Free(void)
{
    if (ArrayData != NULL)
    {
        T*** TmpArray = ArrayData;
        unsigned int Tmpdepth = depth;
        unsigned int Tmpheight = height;

        depth = height = width = 0;
        ArrayData = NULL;
        
        for (unsigned int i = 0;i < Tmpdepth; ++i)
        {
            if (TmpArray[i] != NULL)
            {
                for (unsigned int j = 0;j < Tmpheight; ++j)
                    if (TmpArray[i][j] != NULL)
                        delete[] TmpArray[i][j];

                delete[] TmpArray[i];
            }
        }

        delete [] TmpArray;
    }
}

//-----------------------------------------------------------------

template <class T> T*** ARRAY3D <T> :: Ptr(void)
{
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    return ArrayData;
}

//-----------------------------------------------------------------

template <class T> void ARRAY3D <T> :: SwapContents(ARRAY3D<T>& Array)
{
    std::swap(Array.ArrayData, ArrayData);
    std::swap(Array.height, height);
    std::swap(Array.width,  width);
    std::swap(Array.depth,  depth);
}

//-----------------------------------------------------------------

template <class T> ARRAY3D <T>& ARRAY3D <T> :: operator = (const ARRAY3D<T> &aArray)
{
    if (this == &aArray)
        return *this;

    if (aArray.depth != aArray.depth || height != aArray.height || width != aArray.width)
        Free();

    New(aArray.depth, aArray.height, aArray.width);

    for (unsigned int d=0 ; d<depth  ; ++d)
    for (unsigned int h=0 ; h<height ; ++h)
        memcpy(ArrayData[d][h], aArray.ArrayData[d][h], sizeof(T)*width);

    return *this;
}

//-----------------------------------------------------------------

template <class T> ARRAY3D <T>& ARRAY3D <T> :: operator = (T val)
{
    AssignAllValue(val);
    return *this;
}

//-----------------------------------------------------------------

template <class T> void ARRAY3D <T> :: AssignAllValue(T val)
{
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    for (unsigned int d=0 ; d<depth  ; ++d)
    for (unsigned int h=0 ; h<height ; ++h)
    for (unsigned int w=0 ; w<width  ; ++w)
        ArrayData[d][h][w] = (T)val;
}

//-----------------------------------------------------------------

template <class T> ARRAY3D <T>& ARRAY3D <T> :: operator += (const int number)
{
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    for (unsigned int d=0 ; d<depth  ; ++d)
    for (unsigned int h=0 ; h<height ; ++h)
    for (unsigned int w=0 ; w<width  ; ++w)
        ArrayData[d][h][w] += (T)number;

    return *this;
}

//-----------------------------------------------------------------

template <class T> ARRAY3D <T>& ARRAY3D <T> :: operator -= (const int number)
{
    if (NULL == ArrayData)
        throw std::logic_error("Use operator before Allocate memory or New().");

    for (unsigned int d=0 ; d<depth  ; ++d)
    for (unsigned int h=0 ; h<height ; ++h)
    for (unsigned int w=0 ; w<width  ; ++w)
        ArrayData[d][h][w] -= (T)number;

    return *this;
}


#endif
