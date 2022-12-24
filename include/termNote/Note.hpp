#pragma once
#include <string>

namespace termnote
{
    class Note
    {
    private:
        std::string m_Description;
        bool m_Completed = false;

    public:
        Note(const std::string_view description);
        Note(const std::string_view description, bool completed);
        ~Note();

        [[nodiscard]] inline bool get_completed() { return this->m_Completed;};
        [[nodiscard]] inline const bool get_completed() const { return this->m_Completed; };
        [[nodiscard]] inline std::string_view get_description() { return this->m_Description; };

        std::string to_string();
        const std::string to_string() const;
    };
}