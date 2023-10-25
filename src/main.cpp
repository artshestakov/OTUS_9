#include "cmd.h"
#include "writer_thread.h"
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    WriterThread::Instance().Start(2);

    cmd c;

    WriterConsole writer_console(&c);
    WriterFile writer_file(&c);

    //Парсим аргумент
    if (!c.ParseArgument(argc, argv))
    {
        std::cout << c.GetErrorString() << std::endl;
        return 1;
    }

    //Вызываем режим чтения консоли
    c.ReadConsole();

    return 0;
}
//-----------------------------------------------------------------------------
