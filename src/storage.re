open Belt;

[@bs.val] external unsafeJsonParse : string => 'a = "JSON.parse";

let _storageNamespace = "reason-react-todo";

let saveTodos = (todos: list(TodoItem.todo)) =>
  switch (Js.Json.stringifyAny(List.toArray(todos))) {
  | None => ()
  | Some(str) => Dom.Storage.(localStorage |> setItem(_storageNamespace, str))
  };

let loadTodos = () =>
  switch (Dom.Storage.(localStorage |> getItem(_storageNamespace))) {
  | None => []
  | Some(todosStr) =>
    let todos: list(TodoItem.todo) =
      List.fromArray(unsafeJsonParse(todosStr));
    todos;
  };
