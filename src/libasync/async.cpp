#include "cmd.h"
#include "writer_thread.h"
#include "async.h"
//-----------------------------------------------------------------------------
struct AsyncHandle
{
    AsyncHandle(size_t bulk)
        : CMD(bulk),
        OutConsole(&CMD),
        OutFile(&CMD)
    {

    }

    cmd CMD; //���������������� ������, ������� � ������������ ����� �������� � ��������� ������ �� ���� CMD

private:
    WriterConsole OutConsole;
    WriterFile OutFile;
};
//-----------------------------------------------------------------------------
async::handle_t async::connect(size_t bulk)
{
    //��������� ������ ������ ���� ��� ��� �� ���� ��������
    if (!WriterThread::Instance().IsRun())
    {
        //��� ������� ������� ������� �������, ������� ������ ��������.
        //� ���� ����� ������� ������� 0, ������ ������
        auto thread_count = std::thread::hardware_concurrency();
        if (thread_count == 0)
        {
            return nullptr;
        }

        WriterThread::Instance().Start(thread_count);
    }

    return (new AsyncHandle(bulk));
}
//-----------------------------------------------------------------------------
void async::receive(handle_t handle, const char* data, size_t size)
{
    AsyncHandle *h = static_cast<AsyncHandle*>(handle);
    if (!h)
    {
        //�������� ����� ����� ������� ����������...
        return;
    }

    h->CMD.ReadConsole(std::string(data, size));
}
//-----------------------------------------------------------------------------
void async::disconnect(handle_t handle)
{
    delete handle;
}
//-----------------------------------------------------------------------------
