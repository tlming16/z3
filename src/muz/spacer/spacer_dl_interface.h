/*++
Copyright (c) 2017 Microsoft Corporation and Arie Gurfinkel

Module Name:

    spacer_dl_interface.h

Abstract:

    SMT2 interface for the datalog SPACER

Author:


Revision History:

--*/

#ifndef _SPACER_DL_INTERFACE_H_
#define _SPACER_DL_INTERFACE_H_

#include "util/lbool.h"
#include "muz/base/dl_rule.h"
#include "muz/base/dl_rule_set.h"
#include "muz/base/dl_engine_base.h"
#include "util/statistics.h"

namespace datalog {
class context;
}

namespace spacer {

class context;

class dl_interface : public datalog::engine_base {
    datalog::context& m_ctx;
    datalog::rule_set m_spacer_rules;
    datalog::rule_set m_old_rules;
    context*          m_context;
    obj_map<func_decl, func_decl*> m_pred2slice;
    ast_ref_vector    m_refs;

    void check_reset();

public:
    dl_interface(datalog::context& ctx);
    ~dl_interface();

    lbool query(expr* query);

    lbool query_from_lvl(expr* query, unsigned lvl);

    void display_certificate(std::ostream& out) const;

    void collect_statistics(statistics& st) const;

    void reset_statistics();

    expr_ref get_answer();

    expr_ref get_ground_sat_answer();

    void get_rules_along_trace(datalog::rule_ref_vector& rules);

    unsigned get_num_levels(func_decl* pred);

    expr_ref get_cover_delta(int level, func_decl* pred);

    void add_cover(int level, func_decl* pred, expr* property);

    void add_invariant(func_decl* pred, expr* property);

    expr_ref get_reachable(func_decl *pred);

    void updt_params();

    model_ref get_model();

    proof_ref get_proof();

};
}


#endif
