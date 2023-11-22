#pragma once
//-----------------------------------------------------------------------------
#include "observer.h"
#include "writers.h"
//-----------------------------------------------------------------------------
class cmd : public Observable
{
public:
    cmd(unsigned int block_count = 0);
    ~cmd();

    //! �������� �� �������
    //! \param object ���������
    void Subscribe(Observer* object) override;

    //! �������� ��������� �������� ��������� ������
    //! \return ���������� ��������� �������� ��������� ������
    const std::string& GetErrorString() const;

    //! ������� ��������� ���������� ������
    //! \param argc ���-�� ����������
    //! \param argv ������ � �����������
    //! \return ���������� true � ������ ������, ����� - false
    bool ParseArgument(int argc, char** argv);

    //! ����� ������ ������ �� �������
    void ReadConsole();

    void ReadConsole(const std::string& command);

private:
    //! �������� ������� � ������
    //! \param command �������
    void AddCommand(const std::string& command);

    //! ����������� ����������� ������� �� ������� � �������� ������
    void PrintAndClearVector();

    //! ������ ������
    //! \param s ������
    void Notify(const std::string& s);

    //! �������� ������ �����
    //! \param block_count ������ �����
    void SetBlockCount(unsigned int block_count);

private:
    std::string m_ErrorString;
    unsigned int m_BlockCount;
    int m_BlockDepth;
    std::vector<std::string> m_Vector;
    std::optional<std::chrono::system_clock::time_point> m_Time;
    std::vector<Observer*> m_Subscribers;
};
//-----------------------------------------------------------------------------
