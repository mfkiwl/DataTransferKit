//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   core/Mapper.hh
 * \author Stuart Slattery
 * \date   Tue Nov 08 12:31:05 2011
 * \brief  Mapper class defintion.
 * \note   Copyright (C) 2011 Oak Ridge National Laboratory, UT-Battelle, LLC.
 */
//---------------------------------------------------------------------------//
// $Id: template.hh,v 1.4 2008/01/02 17:18:47 9te Exp $
//---------------------------------------------------------------------------//

#ifndef core_Mapper_hh
#define core_Mapper_hh

#include <string>
#include <list>

#include "Transfer_Map.hh"
#include "Message_Buffer.hh"
#include "Physics.hh"
#include "utils/SP.hh"
#include "utils/Packing_Utils.hh"
#include "comm/global.hh"

namespace coupler
{

//===========================================================================//
/*!
 * \class Mapper
 * \brief A mapper class to generate a one way mapping for transfer between a
 * source physics and a target physics.
 *
 * \sa Mapper.cc for detailed descriptions.
 */
/*! 
 * \example core/test/tstMapper.cc
 *
 * Test of Mapper.
 */
//===========================================================================//

template<class DataType_T>
class Mapper 
{
  public:

    //@{
    //! Useful typedefs.
    typedef DataType_T                            DataType;
    typedef int                                   HandleType;
    typedef const HandleType*                     Handle_Iterator;
    typedef int                                   OrdinateType;
    typedef double                                CoordinateType;
    typedef const CoordinateType*                 Coord_Iterator;
    typedef Message_Buffer<OrdinateType>          Message_Buffer_t;
    typedef typename Message_Buffer_t::Buffer     Buffer;
    typedef std::list<Message_Buffer_t>           BufferList;
    typedef typename BufferList::iterator         BufferList_Iterator;
    typedef Physics<DataType>                     Physics_t;
    typedef denovo::SP<Physics_t>                 SP_Physics;
    typedef nemesis::Communicator_t               Communicator;
    typedef denovo::SP<Transfer_Map>              SP_Transfer_Map;
    typedef typename Transfer_Map::Map_Iterator   Map_Iterator;
    typedef typename Transfer_Map::Map_Pair       Map_Pair;
    typedef typename Transfer_Map::Set_Iterator   Set_Iterator;
    typedef typename Transfer_Map::Set_Pair       Set_Pair;
    //@}

  private:

    // Global communicator.
    const Communicator &d_comm_global;

    // Field name.
    const std::string &d_field_name;

    // Source physics.
    SP_Physics d_source;

    // Target physics.
    SP_Physics d_target;

  public:

    //! Constructor.
    Mapper(const Communicator &comm_global,
	   const std::string &field_name,
	   SP_Physics source,
	   SP_Physics target);

    //! Map the field from the source onto the target.
    void map();

  private:

    //! Source physics post receives.
    void source_post_receives(BufferList &buffer_list, bool send_size);

    //! Target physics send to source.
    void target_send(bool send_size);

    //! Source physics process requests.
    void source_process_requests(BufferList &buffer_list, 
				 SP_Transfer_Map new_map,
				 bool send_size);
    
    //! Target physics post receives.
    void target_post_receives(BufferList &buffer_list, bool send_size);

    //! Source physics send to target.
    void source_send(bool send_size);

    //! Target physics process requests.
    void source_process_requests(BufferList &buffer_list,
				 SP_Transfer_Map new_map,
				 bool send_size);
};

} // end namespace coupler

#endif // core_Mapper_hh

//---------------------------------------------------------------------------//
//              end of core/Mapper.hh
//---------------------------------------------------------------------------//
