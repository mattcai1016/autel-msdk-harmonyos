#ifndef IGROUP_MESH_API_H
#define IGROUP_MESH_API_H

#include <memory>
#include <vector>
#include "KeyListener.h"
#include "CompletionListener.h"
#include "ErrorCode.h"

namespace AutelMobileSdk
{
/*
 * 群组相关API
*/
class IGroupMeshApi
{
//接口参数数据结构
public:

    //无人机
    struct Drone
    {
        int id;
        std::string name;
        bool leader; //是否长机, 群组里只能有一个长机
    };

   //群组信息
    struct Group
    {
        int id;
        std::string name;
        int active; //是否受控
        std::vector<Drone> drones;
    };

//接口
public:

    /***
     * 为指定飞机列表创建一个群组
     */
    virtual ErrorCode CreateGroup(std::vector<int> nodeIds, std::string name,
                                  std::shared_ptr<CompletionListener<Group>> listener) = 0;

    /***
     * 解散群组
     * @param groupId 群组ID
     */
    virtual ErrorCode DisbandGroup(int groupId, std::shared_ptr<CompletionListener<int>> listener) = 0;

    /***
     * 修改群组名称
     * @param groupId 群组ID
     * @param name 群组名称
     */
    virtual ErrorCode RenameGroup(int groupId,
                                  std::string name,
                                  std::shared_ptr<CompletionListener<int>> listener) = 0;


    /***
     * 添加飞机到群组
     * @param groupId 群组ID
     * @param nodeIds 飞机nodeId数组
     */
    virtual ErrorCode AddDroneToGroup(int groupId,
                                      std::vector<int> nodeIds,
                                      std::shared_ptr<CompletionListener<int>> listener) = 0;



    /***
     * 从群组删除飞机
     * @param groupId 群组ID
     * @param nodeIds 飞机nodeId数组
     */
    virtual ErrorCode DelDroneFromGroup(int groupId,
                                        std::vector<int> nodeIds,
                                        std::shared_ptr<CompletionListener<void>> listener) = 0;

    /***
     * 设置长机
     * @param groupId 群组ID
     * @param deviceNodeId 设备节点ID
     */
    virtual ErrorCode SetGroupDroneLeader(int groupId,
                                          int deviceNodeId,
                                          std::shared_ptr<CompletionListener<void>> listener) = 0;


    /***
     * 选择群组或者单机
     * @param mode 1=群组, 2=单机，3=全选
     * @param id  mode=1 群组控制：groupId;
     *            mode=2 单机控制：NodeId;
     *            mode=3 全选：此参数被忽略
     */
    virtual ErrorCode SwitchControlMode(int mode,
                                        int id,
                                        std::shared_ptr<CompletionListener<void>> listener) = 0;

    //获取群组列表
    virtual std::shared_ptr<std::vector<Group>> GetGroupList() = 0;


    //获取指定的群组
    virtual std::shared_ptr<Group> GetGroup(int groupId) = 0;

};
}  // namespace AutelMobileSdk

#endif
