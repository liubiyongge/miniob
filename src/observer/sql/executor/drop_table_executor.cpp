#include <memory>

#include "sql/executor/drop_table_executor.h"

#include "session/session.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "common/log/log.h"
#include "storage/table/table.h"
#include "sql/stmt/drop_table_stmt.h"
#include "storage/db/db.h"
#include "sql/operator/string_list_physical_operator.h"

using namespace std;

RC DropTableExecutor::execute(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;
  Stmt *stmt = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session *session = session_event->session();
  ASSERT(stmt->type() == StmtType::DROP_TABLE, 
         "desc table executor can not run this command: %d", static_cast<int>(stmt->type()));

  DropTableStmt *drop_table_stmt = static_cast<DropTableStmt *>(stmt);

  Db *db = session->get_current_db();
  return db->drop_table(drop_table_stmt->table_name().c_str());
}