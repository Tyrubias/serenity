/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, the SerenityOS developers.
 * Copyright (c) 2024, Sam Atkins <atkinssj@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibCodeComprehension/Types.h>
#include <LibGUI/FileIconProvider.h>
#include <LibGUI/Model.h>

namespace HackStudio {

class DeclarationsModel final : public GUI::Model {
public:
    struct Suggestion {
        static Suggestion create_filename(ByteString const& filename);
        static Suggestion create_symbol_declaration(CodeComprehension::Declaration const&);

        bool is_filename() const { return as_filename.has_value(); }
        bool is_symbol_declaration() const { return as_symbol_declaration.has_value(); }

        Optional<ByteString> as_filename;
        Optional<CodeComprehension::Declaration> as_symbol_declaration;
    };

    explicit DeclarationsModel(Vector<Suggestion>&& suggestions)
        : m_suggestions(move(suggestions))
    {
    }

    enum Column {
        Icon,
        Name,
        Filename,
        __Column_Count,
    };
    virtual int row_count(GUI::ModelIndex const& = GUI::ModelIndex()) const override { return m_suggestions.size(); }
    virtual int column_count(GUI::ModelIndex const& = GUI::ModelIndex()) const override { return Column::__Column_Count; }
    virtual GUI::Variant data(GUI::ModelIndex const& index, GUI::ModelRole role) const override;

    Vector<Suggestion> const& suggestions() const { return m_suggestions; }

private:
    Vector<Suggestion> m_suggestions;
};

}
