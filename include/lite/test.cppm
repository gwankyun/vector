export module lite.test;
import std.core;

export
{
    namespace lite
    {
        class Case
        {
        public:
            Case() = default;
            ~Case() = default;

            void require(const char* _expr, bool _result)
            {
                m_case.push_back(std::make_tuple(_expr, _result));
            }

        private:
            std::vector<std::tuple<std::string, bool>> m_case;
        };

        class Test
        {
        public:
            Test() = default;
            ~Test() = default;

            void addCase(std::string _case)
            {
                Case c;
                m_case[_case] = c;
            }

        private:
            std::map<std::string, Case> m_case;
        };
    }
}
